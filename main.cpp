#include <iostream>
#include <mysql.h>
#include <cstdio>
#include "connectionPool.h"
#include <thread>
using namespace std;
//���̣߳�ʹ��/��ʹ�����ӳ�
//���̣߳�ʹ��/��ʹ�����ӳ�
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
    //�����ӳ� ���߳���ʱ 9283ms
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    op1(0,5000);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto length = end-begin;
    cout << "���߳� �����ӳأ����̣߳���ʱ��" << length.count()/1000000 << "����" <<endl;

    //���ӳ� ���߳���ʱ 550ms
    connectionPool * pool = connectionPool::getConnectionPool();
    chrono::steady_clock::time_point begin1 = chrono::steady_clock::now();
    op2(pool,0,5000);
    chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
    auto length1 = end1-begin1;
    cout << "���߳� ���ӳأ����̣߳���ʱ��" << length1.count()/1000000 << "����" <<endl;
}

void test2(){
    //���߳� �����ӳ�  2107ms
    //���̲߳��룬��Ϊÿһ�ζ�����op1����ȥ�����µ����ӣ���mysql�У���ʹ��ͬһ�û���������ȥ��¼�������һЩ�̵߳�½ʧ�ܣ�Ҳ������˲���ʧ�ܣ��������ݲ���5000��
    //����һ�ζ������Ӿ��ܱ�������������
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
    cout << "���߳� �����ӳأ����̣߳���ʱ��" << length.count()/1000000 << "����" <<endl;

    //���߳� ���ӳ� 125ms
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
    cout << "���߳� ���ӳأ����̣߳���ʱ��" << length1.count()/1000000 << "����" <<endl;
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

//    MYSQL mysql;//���ݿ���
//    MYSQL_RES *res;//��ѯ�����
//    MYSQL_ROW row;//��¼�ṹ��
//
//    //��ʼ�����ݿ�
//    mysql_init(&mysql);
//
//    //�����ַ�����
//    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
//
//    //�������ݿ�
////������Ҫ�����Լ��ı����������룬��ȫΪĬ�ϣ�ֻ�����*��Ϊ�Լ��������Լ���xsgl�����ĳ��Լ����������ݿ⼴��
//    if (mysql_real_connect(&mysql, "127.0.0.1", "root",
//                           "", "testdb", 3306, nullptr, 0) == nullptr) {
//        printf("����ԭ��: %s\n", mysql_error(&mysql));
//        printf("����ʧ�ܣ�\n");
//        system("pause");
//        exit(-1);
//    }
//    cout << 111 <<endl;
//    mysql_close(&mysql);
    return 0;
}