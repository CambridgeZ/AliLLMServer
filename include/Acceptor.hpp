#ifndef __ACCEPTOR_HPP__
#define __ACCEPTOR_HPP__

#include "Socket.hpp"
#include "InetAddress.hpp"

class Acceptor{
public:
    Acceptor(const string &ip, unsigned short port);
    ~Acceptor();
    int accept();//返回connfd
    void ready();
    int fd() const;
private:
    void setReuseAddr();
    void setReusePort();
    void bind();
    void listen();
private:
    Socket _sock; //监听套接字
    InetAddress _addr;
};

#endif // __ACCEPTOR_HPP__