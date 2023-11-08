#include "mySQLConn.h"
#include <mysql.h>
using namespace std;
mySQLConn::mySQLConn() {
    // 参数 mysql -> null
    // 返回值: 该函数将分配、初始化、并返回新对象
    // 通过返回的这个对象去连接MySQL的服务器
    mysql_init(&(this->m_conn));
}

mySQLConn::~mySQLConn() {
    if(&(this->m_conn)!= nullptr){
        mysql_close(&(this->m_conn));
    }
    this->freeResult();
}

bool mySQLConn::connect(string user, string pswd, string dbName, string ip, unsigned short port) {
    //接收const char * 传进来的是string 不匹配，要把string转为char * 才行
    mysql_options(&(this->m_conn), MYSQL_SET_CHARSET_NAME, "gbk");
    // 参数 mysql -> null
    // 返回值: 该函数将分配、初始化、并返回新对象
    // 通过返回的这个对象去连接MySQL的服务器
    MYSQL * ptr = mysql_real_connect(&(this->m_conn),ip.c_str(), user.c_str(), pswd.c_str(), dbName.c_str(), port, nullptr, 0);
//    if(ptr== nullptr){
//        cout << mysql_error(&(this->m_conn)) <<endl;
//    }
    return ptr!= nullptr;
}

bool mySQLConn::update(string sql) {
//    // 执行一个sql语句, 添删查改的sql语句都可以
//    int mysql_query(MYSQL *mysql, const char *query);
//    参数:
//    - mysql: mysql_real_connect() 的返回值
//    - query: 一个可以执行的sql语句, 结尾的位置不需要加 ;
//    返回值:
//    - 如果查询成功，返回0。如果是查询, 结果集在mysql 对象中
//    - 如果出现错误，返回非0值。

    if(mysql_query(&(this->m_conn),sql.c_str())){
        return false;
    }
    return true;
}

bool mySQLConn::query(string sql) {
    this->freeResult();
    if(mysql_query(&(this->m_conn),sql.c_str())){
        return false;
    }

    // 将结果集从 mysql(参数) 对象中取出
    // MYSQL_RES 对应一块内存, 里边保存着这个查询之后得到的结果集
    // 如何将行和列的数据从结果集中取出, 需要使用其他函数
    // 返回值: 具有多个结果的MYSQL_RES结果集合。如果出现错误，返回NULL。
    this->m_result = mysql_store_result(&(this->m_conn));
    return true;
}

bool mySQLConn::next() {
    if(this->m_result!= nullptr){

    //        typedef char** MYSQL_ROW;
    //        遍历结果集的下一行
    //        如果想遍历整个结果集, 需要对该函数进行循环调用
    //        返回值是二级指针, char** 指向一个什么类型的内存呢?
    //    -- 指向一个指针数组, 类型是数组,里边的每个元素都是指针, char* 类型
    //    -- char* []; 数组中的字符串对应的一列数据
    //
    //        需要对 MYSQL_ROW 遍历就可以得到每一列的值
    //        如果要遍历整个结果集, 需要循环调用这个函数
    //        MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);
    //        参数:
    //        - result: 通过查询得到的结果集
    //        返回值:
    //        - 成功: 得到了当前记录中每个字段的值
    //        - 失败: NULL, 说明数据已经读完了

        this->m_row = mysql_fetch_row(this->m_result);
        if(this->m_row!= nullptr){
            return true;
        }
    }
    return false;
}

string mySQLConn::value(int index) {
    // 从结果集中列的个数
    // 参数: 调用 mysql_store_result() 得到的返回值
    // 返回值: 结果集中的列数
    int rowColum = mysql_num_fields(this->m_result);
    if(index>=rowColum||index<0){
        return string();
    }
    char * val = m_row[index];
    //char * val中可能有\0
    //若查询字段中有\0,则转为字符串string只能转换一部分,所以获取当前字段长度，再进行构造

    /*
    返回结果集内当前行的列的长度:
        1. 如果打算复制字段值，使用该函数能避免调用strlen()。
        2. 如果结果集包含二进制数据，必须使用该函数来确定数据的大小，原因在于，对于包含Null字符的任何字段，strlen()将返回错误的结果。
    */

    //    unsigned long *mysql_fetch_lengths(MYSQL_RES *result);
    //    参数:
    //    - result: 通过查询得到的结果集
    //    返回值:
    //    - 无符号长整数的数组表示各列的大小。如果出现错误，返回NULL。


    unsigned  long length = mysql_fetch_lengths(this->m_result)[index];
    return string(val,length);
}
// mysql中默认会进行事务的提交
// 因为自动提交事务, 会对我们的操作造成影响
// 如果我们操作的步骤比较多, 集合的开始和结束需要用户自己去设置, 需要改为手动方式提交事务


//       my_bool mysql_autocommit(MYSQL *mysql, my_bool mode)
//参数:
//        如果模式为“1”，启用autocommit模式；如果模式为“0”，禁止autocommit模式。
//        返回值：如果成功，返回0，如果出现错误，返回非0值。
//
// 事务提交
//        my_bool mysql_commit(MYSQL *mysql);
//        返回值: 成功: 0, 失败: 非0
//
// 数据回滚
//        my_bool mysql_rollback(MYSQL *mysql)
//        返回值: 成功: 0, 失败: 非0



bool mySQLConn::transaction() {
    return mysql_autocommit(&(this->m_conn),false);
}

bool mySQLConn::commit() {
    return mysql_commit(&(this->m_conn));
}

bool mySQLConn::rollback() {
    return mysql_rollback(&(this->m_conn));
}

void mySQLConn::freeResult() {
    if(this->m_result){
        mysql_free_result(this->m_result);
    }
}

void mySQLConn::refreshAliveTime() {
    this->m_alivetime = chrono::steady_clock::now();
}

long long mySQLConn::getAliveTime() {
    chrono::nanoseconds res = chrono::steady_clock::now()-this->m_alivetime;
    //将精度从纳秒向毫秒转换
    chrono::milliseconds millisec = chrono::duration_cast<chrono::milliseconds>(res);
    return millisec.count();
}
