#include "head.h"


using namespace std;

int main() 
{
    int fdSource = open("source.txt", O_RDONLY);
    int len = lseek(fdSource, 0, SEEK_END);
    void *ptrSource = mmap(NULL, len, PROT_READ, MAP_SHARED, fdSource,0);
    if(ptrSource == MAP_FAILED)
    {
        perror("mmap");
        exit(-1);
    }

    int fdTarget = open("target.txt", O_RDWR | O_CREAT,0664);
    truncate("target.txt",len);
    write(fdTarget,"",1);
    void *ptrTarget = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fdTarget,0);
    if(ptrTarget == MAP_FAILED)
    {
        perror("mmap");
        exit(-1);
    }
    memcpy(ptrTarget,ptrSource,len);

    close(fdTarget);
    close(fdSource);
    munmap(ptrTarget, len);
    munmap(ptrSource, len);

    return 0;

}