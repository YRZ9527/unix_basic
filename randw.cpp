#include"head.h"

int main() {
    int srcfd = open("1.txt",O_RDONLY | O_CREAT );
    if (srcfd == -1) {
        perror("open");
        return 1;
    }

    int destfd = open("cpy.txt",O_RDWR | O_CREAT | O_APPEND,0664);
    if (destfd == -1) 
    {
        perror("copy");
        return 1;
    }

    char buf[1024] = {0};
    int len = 0;
    while((len = read(srcfd,buf,sizeof(buf)))>0) {
        write(destfd,buf,len);
    }
    close(destfd);
    close(srcfd);
    return 0;
}