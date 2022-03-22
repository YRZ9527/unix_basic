#include "head.h"

int main() {

    int fd = open("dup2.txt",O_RDWR | O_CREAT,0664);
    if(-1 == fd) {
        perror("open");
        return -1;
    }
    
    int fd1 = open("dup2_new.txt",O_RDWR | O_CREAT ,0644);
    if (-1 == fd1) 
    {
        perror("open");
        return -1;
    }


    cout<<"fd ="<<fd<<","<<"newfd="<<fd1<<endl;

    int dup2_flag = dup2(fd,fd1);
    if (-1 == dup2_flag)
    {
        perror("dup2");
        return -1;
    }



    char* str = "dup2 test";
    int len = write(fd1,str,strlen(str));
    if(len == -1)
    {
        perror("wirte");
        return -1;
    }

    close(fd);
    close(fd1);
    return 0;
}