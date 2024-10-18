#include "../include/Acceptor.hpp"

Acceptor::Acceptor(const string &ip, unsigned short port):_sock(), _addr(ip, port){}

void Acceptor::setReuseAddr(){
    int on = 1;
    // 设置地址复用，防止time_wait状态
    int ret = setsockopt(_sock.getFd(),SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    if(ret){
        perror("setsockopt");
        return ;
    }
}


void Acceptor:: setReusePort(){
    int on = 1;
    // 设置端口复用
    int ret = setsockopt(_sock.getFd(), SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
    if(ret == -1){
        perror("setsockopt");
        return ;
    }
}

void Acceptor:: bind(){
    // 绑定地址
    int ret = ::bind(_sock.getFd(), (struct sockaddr*)_addr.getInetAddrPtr(), sizeof(struct sockaddr));
    if(ret == -1){
        perror("bind");
        return ;
    }
}

void Acceptor:: listen(){
    // 对于socket进行监听，最大连接数为128
    int ret = ::listen(_sock.getFd(), 128);
    if(ret == -1){
        perror("listen");
        return ;
    }
}


int Acceptor::accept(){
    // 接受连接
    int connfd = ::accept(_sock.getFd(), NULL, NULL);
    if(connfd == -1){
        perror("accept");
        return -1;
    }
    return connfd;
}

void Acceptor::ready(){
    // 设置地址复用
    setReuseAddr();
    // 设置端口复用
    setReusePort();
    // 绑定地址
    bind();
    // 监听
    listen();
}

int Acceptor::fd() const{
    return _sock.getFd();
}

Acceptor::~Acceptor(){
    close(_sock.getFd());
}


