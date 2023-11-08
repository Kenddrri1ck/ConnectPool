#include "connectionPool.h"
#include "json/json.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <memory>
using namespace Json;
//因为是多线程操作，共享资源是 this->m_connectionQ ,所以在操作共享资源时一定要加锁。
connectionPool *connectionPool::getConnectionPool() {
    static connectionPool pool;  //第一次调用时，静态局部对象被创建，之后再调用就会直接访问这块内存
                                 //不同于局部变量，局部变量会每次在作用域内创建，离开作用域销毁
    return &pool;
}

bool connectionPool::parseJsonFile() {
    ifstream ifs;
    ifs.open("dbconf.json",ios::in);
    Reader rd;
    Value root;
    rd.parse(ifs,root);
    if(root.isObject()){
        this->m_ip = root["ip"].asString();
        this->port = root["port"].asInt();
        this->m_user = root["user"].asString();
        this->m_pswd = root["password"].asString();
        this->m_minSize = root["minSize"].asInt();
        this->m_maxSize = root["maxSize"].asInt();
        this->m_maxIdleTimeout = root["maxIdleTimeout"].asInt();
        this->m_timeout = root["timeout"].asInt();
        this->m_dbName = root["dbName"].asString();
        return true;
    }
    return false;
}

connectionPool::connectionPool() {
    if(!this->parseJsonFile()){
        return;
    }
    for(int i = 0;i<this->m_minSize;i++){
       addConnection();
    }
    //新建两个线程，一个创建新的数据库连接，一个销毁不用的数据库连接
    thread producer(&connectionPool::produceConnection,this); //用于创建连接
    thread recycler(&connectionPool::recycleConnection,this); //用于销毁连接

    //与主线程分离 调用 detach
    producer.detach();
    recycler.detach();
    //独立的线程 detach掉了  所以可以一直挂载运行
}

//生产者
void connectionPool::produceConnection() {
    while(true){
        unique_lock<mutex> locker(this->m_mutexQ);  //初始化时就会加锁
        //当线程池中的线程数量大于最小值时，阻塞，不产生新的线程
        while(this->m_connectionQ.size()>=this->m_minSize){
            this->m_cond.wait(locker);
        }
        addConnection();
        //唤醒消费者线程，开始获取队列中的连接;
        this->m_cond.notify_all();
        //这里的本意是唤醒消费者线程，但是也会唤醒生产者线程，但是生产者线程有且仅有一个，所以不会被唤醒,
        // 就算有多个生产者也没有影响，因为唤醒后，继续执行循环，如果不符合要求，则会继续被阻塞
        //如果代码功能比较复杂，则生产者和消费者应该各对应一个条件变量
    }
}
//当空闲连接过多时 回收部分连接
void connectionPool::recycleConnection() {
    while(true){
        this_thread::sleep_for(chrono::seconds(1));
        lock_guard<mutex> locker(this->m_mutexQ);  //locker时局部变量 在离开作用域后调用析构函数，就会解锁
        //队列中的连接都是空闲的连接
        while(this->m_connectionQ.size()>this->m_minSize){
            mySQLConn * conn = this->m_connectionQ.front();
            //计算函数在队列中的时长，函数在队列中的时长有两种情况
            //1.被创建后直接加入
            //2.在被使用后再次放回队列
            //我们应该计算使用后被放回队列后的时长，主要方法是记录开始空闲的时间点
            if(conn->getAliveTime()>=this->m_maxIdleTimeout){
                this->m_connectionQ.pop();
                delete conn;
            }else{
                break;
            }
        }
    }
}
//addConnection不需要加锁，因为在外面调用这个函数的地方已经加过了
void connectionPool::addConnection() {
    mySQLConn * conn = new mySQLConn;
    conn->connect(this->m_user,this->m_pswd,this->m_dbName,this->m_ip,this->port);
    conn->refreshAliveTime();
    this->m_connectionQ.push(conn);
}
//消费者
shared_ptr<mySQLConn> connectionPool::getConnection() {
    unique_lock<mutex> locker(this->m_mutexQ);
    while(this->m_connectionQ.empty()){
        //如果为空  则阻塞一定的毫秒数
        //两种方式可以唤醒
        //1.this->m_cond.notify_all()或者this->cond.notify_one()
        //2.
        if(cv_status::timeout == this->m_cond.wait_for(locker,chrono::milliseconds(this->m_timeout))){  //如果达到阻塞时间
            //如果队列扔为空
            if(this->m_connectionQ.empty()){
                continue;
            }
        }
    }
    //使用共享指针的目的是避免数据库连接被频繁的创建和回收，shared_ptr构造函数的第二个参数可以指定删除器，
    // 表明在释放对象时要做的动作，我们可以不释放数据库的连接，而是把数据库的连接再次添加到连接池中连接队列的尾部
    //使用lambda表达式，在shared_ptr释放数据库连接时，将连接添加回连接池中的连接队列尾部
    shared_ptr<mySQLConn> connptr(this->m_connectionQ.front(),[this](mySQLConn * conn){
        //locker_guard在初始化时直接上锁，在作用域结束时调用析构函数解锁
        lock_guard<mutex> locker(this->m_mutexQ);
        conn->refreshAliveTime();
        this->m_connectionQ.push(conn);
    });
    this->m_connectionQ.pop();
    //取出连接之后，唤醒生产者，判断是否往连接池的连接队列中加入连接
    this->m_cond.notify_all();
    //这里调用notify_all本意是唤醒生产者，但是把消费者也唤醒了，但是在上面的99行waitfor处，
    // 虽然被唤醒了，但是判断若连接队列为空，则continue,继续被阻塞了。
    //61行的生产者里的notify_all本意是唤醒消费者线程，但是也会唤醒生产者线程，但是生产者线程有且仅有一个，所以不会被唤醒
    // 就算有多个生产者也没有影响，因为唤醒后，继续执行循环，如果不符合要求，则会继续被阻塞
    //如果代码功能比较复杂，则生产者和消费者应该各对应一个条件变量
    return connptr;
}

connectionPool::~connectionPool() {
    while(!this->m_connectionQ.empty()){
       mySQLConn * conn = this->m_connectionQ.front();
       this->m_connectionQ.pop();
       delete conn;
    }
}