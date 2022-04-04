#include "iostream"
#include "head.h"

int setNonblock(int fd){
    int flags = fcntl(fd, F_GETFL, 0);
    if(flags < 0){
        std::cout<<"F_GETFL failed: "<< strerror(errno)<<std::endl;
        return -1;
    }
    flags |= O_NONBLOCK;
    if(fcntl(fd, F_SETFL, flags)<0)
    {
        cout<<"F_SETFL failed: "<< strerror(errno)<<endl;
        return -1;
    }
}


int main() {
//定义端口号以及ip地址
    const int port = 9007;
    const string ip = "127.0.0.1";
//定义套接字

//AF_INET ipv4
//SOCK_STREAM 字节流 tcp
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock < 0)
    {
        cout << "set socket option reuse address error" << strerror(errno) << endl;
        return 0;
    }
    int opt = 1;
    if(setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt,sizeof(opt)) < 0)
    {
        std::cout << "set socket option reuse address falied:" << strerror(errno) << std::endl;
    }