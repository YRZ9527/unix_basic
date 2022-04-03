#include "head.h"

#define SERVERIP "127.0.0.1"
#define PORT 6789

int main() 
{
    //创建socket AF_INET  :IPV4
    //使用tcp协议
    //创建一个信箱
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
    {
        perror("socket");
        return -1;
    }
    //绑定 创建信箱
    struct sockaddr_in server_addr;
    server_addr.sin_family = PF_INET; //PF_UNIX文件的路径名，长度可达到108字节


}