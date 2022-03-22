#include "head.h"


int main() {
    int fd = open("1.txt", O_RDWR);
    if(-1 == fd) {
        perror("open");
        return 0;
    }


// get flag
    int flag = fcntl(fd, F_GETFL);
    if(flag == -1) {
        perror("fcntl");
        return -1;
    }

    flag |= O_APPEND;

//change flag  add append 
    int ret = fcntl(fd, F_SETFL,flag);
    if(ret == -1)
    {
        perror("fcntl");
        return -1;
    }

    char* str = "hell";

    int wr_flag = write(fd,str,strlen(str));
    if(wr_flag == -1)
    {
        perror("write");
        return -1;
    }

    close(fd);
    return 0;
}