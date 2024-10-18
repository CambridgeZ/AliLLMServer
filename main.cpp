#include <iostream>
#include <string>
#include "./include/EventLoop.hpp"
#include "./include/Acceptor.hpp"
#include "./include/TcpConnection.hpp"
#include "./include/LLMApi.hpp"


using std::string;


void onNewConnection(const TcpConnectionPtr& conn){
    conn->send("welcome to server.\r\n");
    std::cout << conn->toString() << " has connected." << std::endl;
}

void onMessage(const TcpConnectionPtr& conn){
    std::string msg = conn->recieve();
    std::cout << "recv msg: " << msg << std::endl;
    // echo
    /*
        这里可以进行其他的业务逻辑的处理
    */
    static LLMApi llm;
    string response = llm.getResponse(msg);
    conn->send(response);
}

void onClose(const TcpConnectionPtr& conn){
    std::cout << conn->toString() << " has closed." << std::endl;
}

int main(int argc, char *argv[]){
    Acceptor acceptor("127.0.0.1", 12345);
    acceptor.ready();

    EventLoop loop(acceptor);
    loop.setNewConnectionCallback(std::move(onNewConnection));
    loop.setMessageCallback(std::move(onMessage));
    loop.setCloseCallback(std::move(onClose));

    loop.loop();
    return 0;
}