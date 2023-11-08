#include <iostream>
#include <mysql.h>
#include <cstdio>
#include "connectionPool.h"
#include <thread>
using namespace std;
//单线程，使用/不使用连接池
//多线程，使用/不使用连接池
void op1(int begin,int end){
    for(int i = begin;i<end;i++){
        mySQLConn conn;
        conn.connect("root","","testdb","127.0.0.1");
        char sql[1024] = {0};
        sprintf(sql,"insert into person values(%d,25,'man','tom')",i+120);
        conn.update(sql);
    }
}

void op2(connectionPool* pool,int begin,int end){
    for(int i = begin;i<end;i++){
        shared_ptr<mySQLConn> conn = pool->getConnection();
        char sql[1024] = {0};
        sprintf(sql,"insert into person values(%d,25,'man','tom')",i+6200);
        conn->update(sql);
    }
}

void test1(){
    //非连接池 单线程用时 9283ms
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    op1(0,5000);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto length = end-begin;
    cout << "单线程 非连接池，单线程，用时：" << length.count()/1000000 << "毫秒" <<endl;

    //连接池 单线程用时 550ms
    connectionPool * pool = connectionPool::getConnectionPool();
    chrono::steady_clock::time_point begin1 = chrono::steady_clock::now();
    op2(pool,0,5000);
    chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
    auto length1 = end1-begin1;
    cout << "单线程 连接池，单线程，用时：" << length1.count()/1000000 << "毫秒" <<endl;
}

void test2(){
    //多线程 非连接池  2107ms
    //多线程插入，因为每一次都会在op1里面去创建新的连接，在mysql中，都使用同一用户名和密码去登录，会造成一些线程登陆失败，也就造成了插入失败，所以数据不够5000条
    //进行一次额外连接就能避免这样的问题
    mySQLConn conn;
    conn.connect("root","","testdb","127.0.0.1");
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    thread t1(op1,1,1000);
    thread t2(op1,1000,2000);
    thread t3(op1,2000,3000);
    thread t4(op1,3000,4000);
    thread t5(op1,4000,5000);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto length = end-begin;
    cout << "多线程 非连接池，单线程，用时：" << length.count()/1000000 << "毫秒" <<endl;

    //多线程 连接池 125ms
    connectionPool * pool = connectionPool::getConnectionPool();
    chrono::steady_clock::time_point begin1 = chrono::steady_clock::now();
    thread t6(op2,pool,1,1000);
    thread t7(op2,pool,1000,2000);
    thread t8(op2,pool,2000,3000);
    thread t9(op2,pool,3000,4000);
    thread t10(op2,pool,4000,5000);
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();
    chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
    auto length1 = end1-begin1;
    cout << "多线程 连接池，单线程，用时：" << length1.count()/1000000 << "毫秒" <<endl;
}
void query() {
    mySQLConn conn;
    conn.connect("root","","testdb","127.0.0.1");
    string sql = "insert into person values(5,25,'man','tom')";
//    bool flag = conn.update(sql);
//    cout << flag <<endl;

    sql = "select * from person";
    conn.query(sql);
    while(conn.next()) {
        cout << conn.value(0) << ", " << conn.value(1) << ", " << conn.value(2) << ", " << conn.value(3) << endl;
    }
}
int main() {

    test2();
    //connectionPool * pool = connectionPool::getConnectionPool();
    //query();
    //connectionPool  * cp = connectionPool::getConnectionPool();
    //op1(1,2);
    //op2(cp,1,5000);
    std::cout << "Hello, World!" << std::endl;
    system("pause");
    //    MYSQL  mysql;
//    mysql_init(&mysql);
//    MYSQL * ptr = mysql_real_connect(&mysql, "127.0.0.1", "root", "", "testdb", 3306, nullptr, 0);
//    if(ptr== nullptr){
//        cout << 0 <<endl;
//    } else{
//        cout << 1 <<endl;
//    }
//    return 0;

//    MYSQL mysql;//数据库句柄
//    MYSQL_RES *res;//查询结果集
//    MYSQL_ROW row;//记录结构体
//
//    //初始化数据库
//    mysql_init(&mysql);
//
//    //设置字符编码
//    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
//
//    //连接数据库
////这里需要输入自己的本机名和密码，若全为默认，只需更改*处为自己的密码以及”xsgl“处改成自己创建的数据库即可
//    if (mysql_real_connect(&mysql, "127.0.0.1", "root",
//                           "", "testdb", 3306, nullptr, 0) == nullptr) {
//        printf("错误原因: %s\n", mysql_error(&mysql));
//        printf("连接失败！\n");
//        system("pause");
//        exit(-1);
//    }
//    cout << 111 <<endl;
//    mysql_close(&mysql);
    return 0;
}