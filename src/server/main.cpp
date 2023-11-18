#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>

using namespace std;

void resetHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc,char **argv)
{
     if (argc != 3) 
     {
        // 提示用户正确的命令行参数使用方式
        std::cerr << "Usage: " << argv[0] << " <IP_ADDRESS> <PORT>"<<"就是不够三个参数" << std::endl;
        exit(-1);  // 返回非零表示程序异常退出
    }

    signal(SIGINT,resetHandler); 
    
    EventLoop loop;
    // InetAddress addr("127.0.0.1", 6000);
    InetAddress addr(argv[1],stoi(argv[2]));
    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop();

    return 0;
}



