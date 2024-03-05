
/*
muduo给用户提供了两个主要的类
    TcpServer:用于编写服务器程序
    TcpClient:用于编写客户端程序

epoll + 线程池
好处：能够把网络I/O的代码和业务代码区分开
*/

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>

using namespace std;
using namespace muduo;
using namespace muduo::net;

/*
基于muduo网络库开发服务器程序:
1. 组合TcpServer对象
2. 创建EventLoop事件循环对象的指针
*/
class ChatServer
{
public:

private:
    TcpServer _server;  //#1
    EventLoop *_loop;
};