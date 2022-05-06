#include"head.h"

int main() {
    int fd = open("1.txt", O_RDONLY);
    if(-1 == fd) {
        perror("open");
        return 0;
    }
    close(fd);



    return 0;
}