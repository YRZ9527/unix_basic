#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/socket.h>
#include <iostream>
#include <cstring>


int main(){
    const int port = 9007;
    const std::string ip= "127.0.0.1";

    int client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(client_sock < 0){
        std::cout << "create socket failed:" << strerror(errno) << std::endl;
        return 0;
    }

    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    socklen_t len = sizeof(server);

    int opt = 1;
    if(setsockopt(client_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        std::cout << "set socket option reuse address falied:" << strerror(errno) << std::endl;
        return 0;
    }

    if(connect(client_sock, (struct sockaddr*) &server, len)<0){
        std::cout << "connect socket failed:" << strerror(errno) << std::endl;
        return 0;
    }

    std::string msg;
    while(std::cin >> msg){
        if(msg == "EOF")break;
        write(client_sock, msg.c_str(), msg.size());
    }
    close(client_sock);
    return 0;
}

