#ifndef __INETADDRESS_HPP__
#define __INETADDRESS_HPP__

#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <arpa/inet.h>
#include <string.h>

using std::string;

class InetAddress{
public:
    string ip() const;
    unsigned short port() const;
    InetAddress(const string& ip, unsigned short port);
    InetAddress(const struct sockaddr_in& addr);
    ~InetAddress();
    struct sockaddr_in* getInetAddrPtr();
private:
    struct sockaddr_in addr;
};



#endif // __INETADDRESS_HPP__