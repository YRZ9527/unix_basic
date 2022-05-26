#include "iostream"
#include "stdlib.h"
#include "unistd.h"
#include "string"
#include "sys/socket.h"
#include "sys/types.h"
#include "fcntl.h"
#include "assert.h"
 #include <arpa/inet.h>
using namespace std;

const char *s_ip = "127.0.0.1";
const int s_port = 6789;

int main()
{
    // size_t ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET,s_ip,&address.sin_addr);
    address.sin_port = htons(s_port);
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
    auto ret = bind(listenfd, (sockaddr *)&address, sizeof(address));
    // assert(ret != -1);
    ret = listen(listenfd,5);
    

}