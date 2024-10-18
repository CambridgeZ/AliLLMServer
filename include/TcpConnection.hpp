#ifndef __TCPCONNECTION_HPP__
#define __TCPCONNECTION_HPP__

#include "SocketIO.hpp"
#include "Socket.hpp"
#include "InetAddress.hpp"
#include <string>
#include <strstream>
#include <iostream>
#include <memory>
#include <functional>

using std::ostrstream;
using std::string;
using std:: shared_ptr;
using std::function;

class TcpConnection;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr&)>;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>{
public:
    explicit TcpConnection(int fd):_socketIO(fd), _sock(fd), _localAddr(getLocalAddr()), _peerAddr(getPeerAddr()){}
    ~TcpConnection();
    void send(const string &msg);
    string recieve();

    // 注册三个回调函数
    void setNewConnectionCallback(const TcpConnectionCallback& cb){
        onConnectionCb = cb;
    }

    void setMessageCallback(const TcpConnectionCallback& cb){
        onMessageCb = cb;
    }

    void setCloseCallback(const TcpConnectionCallback& cb){
        onCloseCb = cb;
    }

    void handleNewConnectionCallback(){
        if(onConnectionCb){
            // 使用shared_from_this()返回一个指向当前对象的shared_ptr, 以防止TcpConnection对象在回调函数中被销毁
            onConnectionCb(shared_from_this());
        }
        else {
            std::cout << "onConnectionCb is null" << std::endl;
        }
    }
    void handleMessageCallback(){
        if(onMessageCb){
            onMessageCb(shared_from_this());
        }
        else {
            std::cout << "onMessageCb is null" << std::endl;
        }
    }

    void handleCloseCallback(){
        if(onCloseCb){
            onCloseCb(shared_from_this());
        }
        else{
            std::cout << "onCloseCb is null" << std::endl;
        }
    }

    bool isClosed() const {
        char buf[10] = {0};
        int ret = recv(_sock.getFd(), buf, sizeof(buf), MSG_PEEK);

        return 0 == ret;
    }

    // void shutdown(){
    //     _sock.shutdownWrite();
    // }
public:
    string toString() const;
private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();
    TcpConnectionCallback onConnectionCb;
    TcpConnectionCallback onMessageCb;
    TcpConnectionCallback onCloseCb;
    
private:
    SocketIO _socketIO;

    Socket _sock;
    InetAddress _localAddr;
    InetAddress _peerAddr;

};


#endif // __TCPCONNECTION_HPP__