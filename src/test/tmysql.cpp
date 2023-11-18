// #include <muduo/base/Logging.h>
#include <mysql/mysql.h>
#include <string>
#include <iostream>
using namespace std;


static string server="127.0.0.1";
static string user="root";
static string password="123";
static string dbname="chatroom";

// 数据库操作类
class MySQL
{
public:
    // 初始化数据库连接
    MySQL()
    {
            _conn = mysql_init(nullptr);
    }
    // 释放数据库连接资源
    ~MySQL()
    {
        if (_conn != nullptr)
        mysql_close(_conn);
    }
    // 连接数据库
    bool connect()
    {
        MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
                                    password.c_str(), dbname.c_str(), 3306, nullptr, 0);
        if (p != nullptr)
        {
            // C和C++代码默认的编码字符是ASCII，如果不设置，从MySQL上拉下来的中文显示？
            mysql_query(_conn, "set names gbk");
            // LOG_INFO << "connect mysql success!";
        }
        else
        {
            // LOG_INFO << "connect mysql fail!";
        }
        return p;
    }

    // 更新操作
    bool update(string sql)
    {
        cout << sql << endl;
        if (mysql_query(_conn, sql.c_str()))
        {
            // LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                    // << sql << "更新失败!";
            return false;
        }

        return true;
    }

    // 获取连接
    MYSQL* getConnection()
    {
        return _conn;
    }

private:
    MYSQL *_conn;
};

int main()
{
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update("insert into users(name, password, state) values('zhansna', 'zhansna', 'offline')"))
        {
            cout << "成功添加" << endl;
            // 获取插入成功的用户数据生成的主键id
            cout << mysql_insert_id(mysql.getConnection()) << endl;//获得这个链接最新的自增id
            return true;
        }
    }
    cout<< "添加不成功" << endl;
    return false;

    return 0;
}
