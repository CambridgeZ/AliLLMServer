#include <string.h>
#include "../include/InetAddress.hpp"

InetAddress::InetAddress(const string& ip, unsigned short port){
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddress::InetAddress(const struct sockaddr_in& addr):addr(addr){}

string InetAddress::ip() const{
    return string(inet_ntoa(addr.sin_addr));
}

unsigned short InetAddress::port() const{
    return ntohs(addr.sin_port);
}

InetAddress::~InetAddress(){}

struct sockaddr_in* InetAddress::getInetAddrPtr(){
    return &addr;
}





