#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "iostream"
using namespace std;

int main()
{
    cout<<"begin"<<endl;
    //创建套接字
    const int port = 9090;
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));               //每个字节都用0填充
    serv_addr.sin_family = AF_INET;                         //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //具体的IP地址
    serv_addr.sin_port = htons(port);                       //端口
    bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //进入监听状态，等待用户发起请求 数字表示最大的允许数、列表大小
    //一定时间内能达到的最大链接
    listen(serv_sock, 20);

    //接收客户端请求
    char str[] = "Hello World!";
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    //向客户端发送数据

    // for (;;)
    // {
    //     int recvlen = recv(clnt_sock, str, sizeof(str) - 1, 0);
    //     if (recvlen <= 0)
    //         break;
    //     if (strstr(str, "quit") != NULL)
    //     //write(clnt_sock, str, sizeof(str));
    //     cout<<"recv = "<<str<<endl;
    // }

    write(clnt_sock, str, sizeof(str));
    cout<<str<<endl;

    //关闭套接字
    close(clnt_sock);
    close(serv_sock);

    return 0;
}