#include"head.h"

int main() {

    int fd = open("1.txt",O_RDWR);
    if(-1 == fd) {
        perror("open");
        return 1;
    }

    int ret = lseek(fd,100,SEEK_END);
    if(-1 == ret) {
        perror("lseek");
        return 1;
    }
    cout<<ret<<endl;
    write(fd,"t",1);
    close(fd);
    int ret_cur = lseek(fd,0,SEEK_CUR);
    cout<<ret_cur<<endl;



    return 0;
}