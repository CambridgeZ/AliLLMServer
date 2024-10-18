#include "../include/TcpConnection.hpp"

TcpConnection:: ~TcpConnection(){

}

void TcpConnection:: send(const string &msg){
    _socketIO.writen(msg.c_str(),msg.size());
}

string TcpConnection:: recieve(){
    char buff[65535] = {0};
    _socketIO.readline(buff, sizeof(buff));
    // cout<<strlen(buff)<<" "<<buff<<endl;
    return string(buff);
}

string TcpConnection:: toString() const{
    ostrstream oss;
    oss << _localAddr.ip() << ":" << _localAddr.port() << "-->"
        << _peerAddr.ip() << ":" << _peerAddr.port();
    return oss.str();
}

InetAddress TcpConnection:: getLocalAddr(){
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    if(getsockname(_sock.getFd(), (struct sockaddr*)&addr, &len) == -1){
        perror("getsockname");
    }
    return InetAddress(addr);
}

InetAddress TcpConnection:: getPeerAddr(){
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    if(getpeername(_sock.getFd(), (struct sockaddr*)&addr, &len) == -1){
        perror("getpeername");
    }
    return InetAddress(addr);
}

