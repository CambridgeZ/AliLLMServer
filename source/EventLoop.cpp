#include "../include/EventLoop.hpp"
#include "../include/Acceptor.hpp"
#include "../include/TcpConnection.hpp"
#include <unistd.h>
#include <sys/epoll.h>
#include <iostream>
#include <errno.h>

using std::cerr;

EventLoop:: EventLoop(Acceptor& acceptor):epfd(createEpollFd()), evtList(16), isLooping(false), acceptor(acceptor){
    addEpollFdRead(acceptor.fd());// 监听listenfd
}

EventLoop:: ~EventLoop(){
    ::close(epfd);
}

void EventLoop:: loop(){
    if(epfd == -1){
        cerr<< "epfd is -1" << endl;
        return ;
    }
    isLooping = true;
    while(isLooping){
        waitEpollFd();
    }
}

void EventLoop:: unloop(){
    isLooping = false;
}

void EventLoop:: waitEpollFd(){
    int nready = 0;
    do{
        // 监听文件描述符
        nready = epoll_wait(epfd, &*evtList.begin(), evtList.size(), 5000);
    }while(-1 == nready && errno == EINTR);

    cout<< "nready = " << nready << endl;
    
    if(nready == -1){
        // 出现错误
        cerr<< "epoll_wait error, nready= -1" << endl;
        // 查看错误原因
        cout<< "errno: " << errno << endl;
        return ;
    }
    else if(nready == 0){
        // printf("epoll_wait timeout\n");
        cerr<< "epoll_wait timeout" << endl;
    }
    else {
        //  cout<< "nready = " << nready << endl;
        // 判断一下文件描述符是不是已经达到了1024，如果达到了需要进行扩容
        if((size_t)nready == evtList.size()){
            evtList.reserve(2 * nready);
        }
       
        for(size_t idx = 0; (int)idx != nready; ++idx){
            // 查看文件描述符是不是listenfd
            if(evtList[idx].data.fd == acceptor.fd()){
                // 处理新的连接
                if(evtList[idx].events & EPOLLIN){
                    // 处理新的连接
                    handleNewConnection();
                }
            }
            else {
                cout<< "handle message" << endl;
                // 处理消息
                if(evtList[idx].events & EPOLLIN){
                    // 处理消息
                    handleMessage(evtList[idx].data.fd);
                }
            }
        }
    }
}

void EventLoop:: handleNewConnection(){
    int fd = acceptor.accept();

    if(fd < 0){
        perror("handleNewConnection accept");
        return ;
    }

    addEpollFdRead(fd);
    // 建立连接
    TcpConnectionPtr conn(new TcpConnection(fd));

    conn->setNewConnectionCallback(onNewConnectionCb);// 注册链接建立
    conn->setMessageCallback(onMessageCb);// 注册消息到达
    conn->setCloseCallback(oncloseCb);//注册消息断开

    conns[fd] = conn;

    conn->handleNewConnectionCallback();//连接已经建立，可以直接触发
}

void EventLoop:: handleMessage(int fd){
    auto iter = conns.find(fd);
    if(iter == conns.end()){
        printf("no such fd\n");
        return ;
    }
    
    auto conn = iter->second;
    bool flag = conn -> isClosed();

    if(flag){
        // 已经断开了
        conn->handleCloseCallback();
        conns.erase(iter);
    }
    else {
        conn->handleMessageCallback();
    }

    string msg = conn->recieve();
    if(msg.empty()){
        // conn->shutdown();
        conns.erase(iter);
    }
    else {
        conn->send(msg);
    }
}

int EventLoop:: createEpollFd(){
    int fd = :: epoll_create(500);
    if(fd < 0){
        perror("epoll_create");
        return -1;
    }

    return fd;
}


void EventLoop:: addEpollFdRead(int fd){
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;

    int ret = ::epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &evt);

    if(ret < 0 ){
        perror("epoll_ctl_add");
        return ;
    }
}

// 取消文件描述符的监听
void EventLoop:: delEpollReadFd(int fd){
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;

    int ret = ::epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &evt);
    if(ret < 0){
        perror("epoll_ctl_del");
        return ;
    }
}



