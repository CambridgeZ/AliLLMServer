#ifndef __SOCKETIO_HPP__
#define __SOCKETIO_HPP__

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;
using std::size_t;

class SocketIO {
private:
    int _fd;
public:
    explicit SocketIO(int fd):_fd(fd){}
    ~SocketIO(){
        close(_fd);
    }
    int writen(const char *buf, size_t count);
    int readline(char *buf, size_t maxlen);
    int readn(char *buf, size_t count);
    bool isClosed(){
        return _fd == -1;
    }
};

#endif // __SOCKETIO_HPP__