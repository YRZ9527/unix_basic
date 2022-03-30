#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <errno.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <signal.h>
#include <netdb.h>
#include <sys/types.h>

//设置文件描述符非阻塞
static int setNonblock (int fd) {
    if(fd < 0) return -1;
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) {
        return -1;
    }

    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0) {
        return -1;
    }
    return 0;
}

//设置地址可重用
static int setReuseAddr(int fd){
    if(fd < 0) return -1;
    int on = 1;
    if (setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        return -1;
    }
    return 0;
}

int main(){
    
    const int port = 9007;
    const int MAX_EVENT = 20;

    struct epoll_event ev, event[MAX_EVENT];

    const char * const local_addr = "127.0.0.1";
    struct sockaddr_in server_addr = { 0 };
    //初始化socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listenfd) {
        std::cout << "create listenfd failed:" << strerror(errno) << std::endl;
        return -1;
    }
    
    if (setReuseAddr(listenfd) < 0){
        std::cout << "set reuse addr failed:" << strerror(errno) << std::endl;
        close(listenfd);
        return -1;
    }

    server_addr.sin_family = AF_INET;
    inet_aton( local_addr, &(server_addr.sin_addr));
    server_addr.sin_port = htons(port);

    if (bind(listenfd, (const struct sockaddr *)&server_addr, sizeof (server_addr)) < 0) {
        std::cout << "bind port failed:" << strerror(errno) << std::endl;
        close(listenfd);
        return -1;
    }

    if (setNonblock(listenfd) < 0) {
        std::cout << "set listenfd nonblock failed:" << strerror(errno) << std::endl;
        close(listenfd);
        return -1;
    }

    if (listen(listenfd, 200) < 0) {
        std::cout << "listen failed:" << strerror(errno) << std::endl;
        close(listenfd);
        return -1;
    }

    // 创建epoll实例
    int epfd = epoll_create(5);
    if (1 == epfd) {
        std::cout << "create epoll failed" << strerror(errno) << std::endl;
        return -1;
    }

    //添加listenfd 到epoll事件
    ev.data.fd = listenfd;
    ev.events = EPOLLIN | EPOLLET /* 边缘触发选项。 */;
    
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) < 0) {
        std::cout << "epoll add failed:" << strerror(errno) << std::endl;
        close(listenfd);
        close(epfd);
        return 0;
    }

    for( ; ; ){
        int nfds;
        //等待io事件
        nfds = epoll_wait(epfd, event, MAX_EVENT, -1);
        std:: cout << "epoll_wait return" << std::endl;

        for(int i = 0; i < nfds; i++){
            uint32_t events = event[i].events;
            //处理epoll出错和对端关闭情况
            if (events & EPOLLERR || events & EPOLLHUP || (! events & EPOLLIN)) {
                std::cout << "epoll has error" << strerror(errno) << std::endl;
                close (event[i].data.fd);
                continue;
            } else if (event[i].data.fd == listenfd){
                //ET模式下，需要一次把所有数据读完，使用循环读取
                for ( ; ; ){
                    struct sockaddr in_addr = { 0 };
                    socklen_t in_addr_len = sizeof (in_addr);
                    int client_sock = accept(listenfd, nullptr, nullptr);
                    if (client_sock < 0){
                        break;
                    }

                    std::cout << "accept client" << std::endl;

                    if (setNonblock(client_sock) < 0){
                        std::cout << client_sock <<" set non_block falied: " << std::endl; 
                        close(client_sock);
                        return 0;
                    }

                    ev.events = EPOLLIN | EPOLLET;
                    ev.data.fd = client_sock;
                    if (epoll_ctl( epfd, EPOLL_CTL_ADD, client_sock, &ev) < 0){
                        std::cout << client_sock <<" epoll_ctl falied: " << std::endl; 
                        close(client_sock);
                        return 0;
                    }
                }
            } else{
                int done = 0;
                for ( ; ; ){
                    ssize_t result_len;
                    char buf[10] = { 0 };
                    result_len = read(event[i].data.fd, buf, sizeof(buf) - 1);
                       
                    if(result_len == -1){
                        if(errno != EAGAIN && errno != EWOULDBLOCK){
                            done = 1;
                            epoll_ctl( epfd, EPOLL_CTL_DEL, event[i].data.fd, nullptr);
                        }
                        break;
                    }
                    else if(!result_len){
                        done = 1;
                        break;
                    }

                    std::cout << "receive message:" << buf << std::endl;
                }
                if(done){
                    std::cout << "close connection" << std::endl;
                    close(event[i].data.fd);
                }
            }
        }
    }
    close(listenfd);
    close(epfd);
}