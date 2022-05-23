#include "iostream"
#include "arpa/inet.h"
#include "stdlib.h"
#include "unistd.h"
#include "string"
using namespace std;

const char *s_ip = "127.0.0.1";
const int s_port = 6789;

int main()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        std::cerr << "socket error" << endl;
        exit(-1);
    }

    struct sockaddr_in server_addr;
    inet_pton(AF_INET, s_ip, &server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(s_port);
    int ret = bind(listenfd, (sockaddr *)&server_addr,sizeof(server_addr));
    if(ret == -1)
    {
        perror("bind");
        exit(-1);
    }

    return 0;
}