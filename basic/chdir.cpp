#include "head.h"

int main() {
    char buf[128] = {0};

    getcwd(buf, sizeof(buf));
    cout<<buf<<endl;

    int ret = chdir("/Users/zong/Desktop");
    if(ret==-1)
    {
        perror("chdir");
        return -1;
    }
    int fd = open("chdir.txt",O_RDWR|O_CREAT,0664);
    if(fd==-1)
    {
        perror("open");
        return -1;
    }
    write(fd,"t",7);
    close(fd);

    char buf1[128];
    getcwd(buf1,sizeof(buf1));
    cout<<"当前目录"<<buf1<<endl;
    return 0;
}

    