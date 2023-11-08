//
// Created by 34885 on 2023/4/4.
//

#ifndef CONNECTPOOL_CONNECTIONPOOL_H
#define CONNECTPOOL_CONNECTIONPOOL_H
//创建为单例模式
//单例模式分为懒汉模式和饿汉模式
//懒汉模式类被需要时才进行实例化
//饿汉模式无论是否使用该类，都实例化该对象
//在c++11后，实现懒汉模式，使用静态局部变量不会有线程安全问题
//实现懒汉模式要使用互斥锁，因为懒汉模式在对象被需要使用时才会创建，若多个线程需要同时使用，则需要使用互斥锁来保证对象有且仅有一个

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "mySQLConn.h"
using namespace std;
class connectionPool{  //通过类名获取实例，则只可以访问静态函数和静态变量
public:
    static connectionPool * getConnectionPool();
    //因为是单例模式，所以拷贝构造和复制运算符重载都要使用delete
    connectionPool(const connectionPool &obj) = delete;
    connectionPool & operator = (const connectionPool & obj) = delete;
    bool parseJsonFile();
    shared_ptr<mySQLConn>  getConnection();
    ~connectionPool();
private:

    connectionPool();  //因为要单例模式，所以只有一个对象，通过类名访问对象，所以构造函数设为私有 或者 = delete
    void produceConnection();
    void recycleConnection();
    void addConnection();
    queue<mySQLConn*> m_connectionQ;
    string m_ip;
    string m_user;
    string m_pswd;
    string m_dbName;
    unsigned short port;
    int m_maxSize;
    int m_minSize;
    int m_timeout;  //超时时长
    int m_maxIdleTimeout;  //最大空闲时长
    mutex m_mutexQ;  //互斥锁

    //涉及到线程阻塞  用条件变量
    condition_variable m_cond;
};
#endif //CONNECTPOOL_CONNECTIONPOOL_H
