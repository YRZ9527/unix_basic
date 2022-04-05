#include"head.h"

int main()
{

    int ret = -1;
    pid_t pid = -1;
    void *addr = NULL;

    //1、创建匿名映射
    addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,-1, 0);
    if(MAP_FAILED == addr)
    {
        cout<<"error"<<strerror(errno) << std::endl;
        return 1;
    }
    //创建子进程
    pid = fork();
    if(-1 == pid)
    {
        perror("fork");
        munmap(addr,4096);
        return 1;
    }

    //3、父子进程通信
    if(pid == 0)
    {
        memcpy(addr,"12133141",9);

    }
    else
    {
        //父进程读

        wait(NULL);
        cout<<"parent process"<<(char*)addr<<endl;
    }
    //断开映射
    munmap(addr, 4096);
    return 0;
}