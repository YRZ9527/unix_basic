#include "head.h"

int main() {
    int fd = open("mmap_test.txt", O_RDWR);
    
    int size = lseek(fd, 0, SEEK_END);

    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);

    if(ptr == MAP_FAILED){
        perror("mmap");
        exit(-1);
    }

    pid_t pid = fork();
    if(pid > 0){
        wait(NULL);
        char buf[1024];
        strcpy(buf,(char*)ptr);
         printf("recv : %s\n", buf);
        
    }
    else if(pid == 0){
        strcpy((char*)ptr,"i am a message");
    }
    else {
        perror("fork");
        exit(-1);
    }
    munmap(ptr,1024);
    return 0;
}

