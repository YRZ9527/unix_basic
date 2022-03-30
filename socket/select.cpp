#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <errno.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>
//设置文件描述符为非阻塞，避免读文件时阻塞
int setNonblock(int fd){
    int flags = fcntl(fd, F_GETFL, 0);
    if(flags < 0){
        std::cout << "F_GETFL failed:" << strerror(errno) << std::endl;
        return -1;
    }
    flags = flags | O_NONBLOCK;
    if(fcntl(fd, F_SETFL, flags)<0){
        std::cout << "set nonblock failed:" << strerror(errno) << std::endl;
        return -1;
    }
    return 0;
}
int main(){
    //初始化socket
    const std::string ip = "127.0.0.1";
    const int port = 9007;
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock <0){
        std::cout << "create socket failed:" << strerror(errno) << std::endl;
        return -1;
    }
    int opt = 1;
    if(setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        std::cout << "set socket option reuse address falied:" << strerror(errno) << std::endl;
        close(server_sock);
        return 0;
    }
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    server_addr.sin_port = htons(port);
    if(bind(server_sock, (struct sockaddr*)&server_addr, (socklen_t)sizeof(server_addr)) < 0){
        std::cout << "address bind failed:" << strerror(errno) << std::endl;
        close(server_sock);
        return -1;
    }
    if(listen(server_sock, 5) < 0){
        std::cout << "listen ip:" << ip << ",port:" << port << "failed!" << std::endl;
        close(server_sock);
        return -1;
    }
    setNonblock(server_sock);
    //初始化监听集合
    fd_set listen_fds;
    FD_ZERO(&listen_fds);
    FD_SET(server_sock, &listen_fds);
    int maxfd = 4;
    
    while(1){
        fd_set cycle_fds = listen_fds;
        //阻塞等待io事件，select最后一个参数可以传入等待时间，如果传入时间t，将每隔t时间返回一次
        if(select(maxfd+1, &cycle_fds, nullptr, nullptr, nullptr) < 0){
            std::cout << "select error:" << errno <<std::endl;
            close(server_sock);
            return -1;
        }
        std::cout << "select return" << std::endl;
        int fds_size = maxfd;
        for(int fd = 3; fd < fds_size; fd++){
            //FD_ISSET用于判断文件描述符上是否有IO事件发生
            if(FD_ISSET(fd, &cycle_fds)){
                //如果server_sock上有IO事件，说明有新的client请求连接
                if(fd == server_sock){
                    int client_sock = accept(server_sock, nullptr, nullptr);
                    if(setNonblock(client_sock) < 0){
                        std::cout << client_sock <<" set non_block falied: " << std::endl; 
                        close(client_sock);
                        continue;
                    }
                    FD_SET(client_sock, &listen_fds);
                    ++maxfd;
                    std::cout << "accept client" << std::endl;
                }
                //如果不是server_sock上的IO事件，说明发生了读事件。
                else{
                    ssize_t nread;
                    char buf[10] = { 0 };
                    if(nread = read(fd, buf, sizeof(buf)-1) > 0){
                        std::cout << "receive message:" << buf << std::endl;
                    }
                    //nread < 0时，说明对端已经关闭了
                    else if(nread < 0){
                        close(fd);
                        FD_CLR(fd, &listen_fds);
                        --maxfd;
                        std::cout << "remote closed" << std::endl;
                    }
                }
            }
        }
    }
    close(server_sock);
}
