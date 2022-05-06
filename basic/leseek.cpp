#include"head.h"

int main() {
    int fd = -1;
    int ret = -1;
    fd = open("1.txt", O_RDWR);
    if(-1 == fd) {
        perror("open");
        return 1;
    }

    printf("fd = %d\n", fd);


    //2.lseek operation
    
    

    ret = lseek(fd,2,SEEK_SET);
    if(ret == -1) {
        perror("lseek");
        return 1;
    }
    write(fd,"ABCDR",7);
    
    return 0;
}  