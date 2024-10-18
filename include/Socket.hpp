#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sys/epoll.h>

using std::string;

class Socket{
public:
    int getFd() const{
        return fd;
    }
    explicit Socket(int fd);
    Socket();
    ~Socket(){}

private:
    int fd;
};

#endif // __SOCKET_HPP__