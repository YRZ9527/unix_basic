#include "head.h"

int main() {
    int ret = -1;
    int fd  = -1;
    char buf[100];

    fd = open("1.txt", O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        return 1;
    }
    cout<<fd<<endl;

    //2.read file
    memset(buf, 0, sizeof(buf));
    ret = read(fd, buf, sizeof(buf));
    if(ret == -1)
    {
        perror("write");
        return 1;
    }
    cout<<ret<<"->"<<buf<<endl;
    close(fd);
    return 0;
}