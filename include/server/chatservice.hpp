#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
using namespace std;
using namespace muduo;
using namespace muduo::net;

#include "redis.hpp"
#include "usermodel.hpp"
#include "json.hpp"
#include "offlinemsgmodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
using json = nlohmann::json;

// 表示处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;

// 聊天服务器业务类
class ChatService
{
public:
    // 获取单例对象的接口函数
    static ChatService *instance();
    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);

    
    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    
    void addFriend(const TcpConnectionPtr &conn,json &js,Timestamp time);

    MsgHandler getHandler(int msgid);

    void clientCloseException(const TcpConnectionPtr &conn);

    void reset();

    void oneChat(const TcpConnectionPtr &conn,json &js,Timestamp time);
     //创建群组
    void createGroup(const TcpConnectionPtr &conn,json &js,Timestamp time);
     // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
     // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);


    
private:
    ChatService();

    // 存储消息id和其对应的业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;
    // 存储在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;
    // 定义互斥锁，保证_userConnMap的线程安全
    mutex _connMutex;

    UserModel _userModel;

    OfflineMsgModel offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;

    Redis _redis;
};

#endif