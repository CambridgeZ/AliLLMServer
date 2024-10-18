#include "../include/Socket.hpp"

Socket::Socket(){
    fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == fd){
        perror("socket");
        return ;
    }
}

Socket::Socket(int fd):fd(fd){}
