#include "head.h"



int main(int argc, char **argv){
    int fd = open("dup.txt",O_RDWR | O_CREAT,0664);
    if(-1 == fd) {
        perror("open");
        return -1;
    }

    int fd_new = dup(fd);
    if(-1 == fd_new) {
        perror("dup");
        return -1;
    }
    cout<<fd<<"->"<<fd_new<<endl;

    close(fd);

    char *str = "hello.yurongzong";
    int ret = write(fd_new, str, strlen(str));
    
    if (-1 == ret) 
    {
        perror("write");
        return -1;
    }
    close(fd_new);
    return 0;

    
}