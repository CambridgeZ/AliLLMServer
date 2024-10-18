#include "../include/SocketIO.hpp"

int SocketIO::writen(const char *buf, size_t count){
    size_t total = 0;
    while(total < count){
        ssize_t ret = ::write(_fd, buf + total, count - total);
        if(ret == -1 && errno == EINTR){
            continue;
        }else if(ret == -1){
            perror("write");
            return -1;
        }else{
            total += ret;
        }
    }
    return total;
}

int SocketIO::readn(char *buf, size_t count){
    size_t total = 0;
    while(total < count){
        ssize_t ret = ::read(_fd, buf + total, count - total);
        if(ret == -1 && errno == EINTR){
            continue;
        }else if(ret == -1){
            perror("read");
            return -1;
        }else if(ret == 0){
            return total;
        }else{
            total += ret;
        }
    }
    return total;
}

int SocketIO::readline(char *buf, size_t maxlen) {
    int left = maxlen - 1; // 留一个位置给结尾的 '\0'
    char *p = buf;
    int ret = 0, total = 0;

    while (left > 0) {
        ret = ::recv(_fd, p, 1, 0); // 每次只读取一个字符
        if (ret == -1 && errno == EINTR) {
            // 被中断，继续读取
            continue;
        } else if (ret == -1) {
            // 发生错误
            perror("recv");
            return -1;
        } else if (ret == 0) {
            // 连接关闭
            break;
        }

        // 正常读取了一个字符
        if (*p == '\n') {
            // 如果是换行符，结束读取
            p++;
            break;
        }

        p++; // 指向下一个存储位置
        total++;
        left--;
    }

    *p = '\0'; // 添加字符串结束符
    return total; // 返回读取到的字符数量
}
