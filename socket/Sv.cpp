#include"head.h"

using namespace std;
const char* s_ip = "127.0.0.1";
const int s_port = 6789;


int main() {

//create a socket

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0)
    {
        perror("listen fd");
        exit(0);          
    }
//bind
    struct sockaddr_in server_addr;
    server_addr.sin_family = PF_INET;
    //转换为网络字节序
    inet_pton(AF_INET, s_ip, &server_addr);
    server_addr.sin_port = htons(s_port);

    // int ret = bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    auto ret1 = bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

//listen
    int ret = listen(listenfd,8);
    if(ret == -1)
    {
        perror("listen");
        exit(1);
    }


//client connect
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int connfd = accept(listenfd, (struct sockaddr *)&client_addr,&client_addr_len);
    if(connfd == -1)
    {
        perror("accept");
        exit(1);
    }

    char client_ip = {0};
    //bug
    
    inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, sizeof(client_ip));





    unsigned short client_port = ntohs(client_addr.sin_port);
    printf("ip:%s, port:%d\n", client_ip, client_port);
    // 5. 开始通信
    // 服务端先接收客户端信息，再向客户端发送数据
    // 接收数据
    char recv_buf[1024] = {0};
    while (1) {
        ret = read(connfd, recv_buf, sizeof(recv_buf));
        if (ret == -1) {
            perror("read");
            exit(-1);
        } else if (ret > 0) {
            printf("recv client data : %s\n", recv_buf);
        } else {
            // 表示客户端断开连接
            printf("client closed...\n");
            break;
        }
        // 发送数据
        char *send_buf = "hello, i am server";
        // 粗心写成sizeof，那么就会导致遇到空格终止
        write(connfd, send_buf, strlen(send_buf));
    }

    // 关闭文件描述符
    close(connfd);
    close(listenfd);
    return 0;
}