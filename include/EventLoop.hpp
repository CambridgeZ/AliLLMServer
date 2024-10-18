#ifndef __EVENTLOOP_HPP__
#define __EVENTLOOP_HPP__

#include <vector>
#include <map>
#include <memory>
#include <functional>

using std::vector;
using std::map;
using std::shared_ptr;
using std::function;

class Acceptor;
class TcpConnection;

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr&)>; // 回调函数


class EventLoop{
private:
    int epfd; // epoll_create 创建的文件描述符
    vector<struct epoll_event> evtList; // 存放满足条件的文件描述符的数据结构
    bool isLooping; // 标识循环是否在运行
    Acceptor& acceptor;
    map<int, shared_ptr<TcpConnection>> conns; // 文件描述符和连接之间的键值对

private:
    int createEpollFd();// 创建epfd
    void addEpollFdRead(int fd);// 监听文件描述符
    void waitEpollFd(); // 封装epoll_wait
    void handleNewConnection();// 处理新的连接
    void handleMessage(int fd);// 处理连接上的消息
    void delEpollReadFd(int fd);//
    
    TcpConnectionCallback onNewConnectionCb;//连接建立
    TcpConnectionCallback onMessageCb;//消息到达
    TcpConnectionCallback oncloseCb;//连接关闭
 
public:
    EventLoop(Acceptor& acceptor);
    ~EventLoop();
    void loop();//循环
    void unloop();//退出循环

    void setNewConnectionCallback(const TcpConnectionCallback&& cb){
        onNewConnectionCb = std::move(cb);
    }

    void setMessageCallback(const TcpConnectionCallback&& cb){
        onMessageCb = std::move(cb);
    }

    void setCloseCallback(const TcpConnectionCallback&& cb){
        oncloseCb = std::move(cb);
    }
};

#endif // __EVENTLOOP_HPP__