#include "head.h"
using namespace std;
//写文件



int main() {
    //1.只写方式打开文件
    int fd = -1;
    int ret = -1;
    char *str = "hello,world";
    fd = open("1.txt", O_WRONLY | O_APPEND ,0644);
    if(fd == -1) {
        perror("open");
        return 1;
    }
    //2.写文件
    ret = write(fd,str,strlen(str));
    if(ret == -1) {
        perror("write");
        return 1;
    }
    cout<<"write len"<<ret<<endl;
    //3.关闭文件    
    close(fd);

    return 0;
}