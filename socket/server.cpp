//server.cpp

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>


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
    const int port = 9007;
    const std::string ip= "127.0.0.1";

    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock < 0){
        std::cout << "create socket failed:" << strerror(errno) << std::endl;
        return 0;
    }
    int opt = 1;
    if(setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        std::cout << "set socket option reuse address falied:" << strerror(errno) << std::endl;
        return 0;
    }

    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    socklen_t len = sizeof(server);
    
    if(bind(server_sock, (struct sockaddr*) &server, len)<0){
        std::cout << "bind socket failed:" << strerror(errno) << std::endl;
        return 0;
    }

    listen(server_sock, 5);

    char buf[1024];
    while(1){
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        bzero(&client,sizeof(client));
        std::cout << "------------waiting for connect-------------" << std::endl;
        int client_sock = accept(server_sock, (struct sockaddr*) &client, &client_len);
        if(client_sock < 0){
            std::cout << "accept socket failed:" << strerror(errno) << std::endl;
            sleep(1);
            continue; 
        }

        if(setNonblock(client_sock) < 0){
            continue;
        }

        int client_port = ntohs(client.sin_port);
        
        char client_ip[1024];
        const char *ptr = inet_ntop(AF_INET,&client.sin_addr, client_ip, sizeof(client_ip)); 
        if(!ptr){
            std::cout << "transform client address failed:" << strerror(errno) << std::endl;
        }
        int nbytes;
        while(nbytes = read(client_sock, buf, sizeof(buf)-1)>=0){
            if(nbytes==0){
                std::cout << "msg receive complete" << std::endl;
            }
            std::cout << "receive msg:" << buf << std::endl;
        }
        std::cout << "remote port closed:" << strerror(errno) << std::endl;
        close(client_sock);
    }
    close(server_sock);
    return 0;
}

