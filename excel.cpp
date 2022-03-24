#include <unistd.h>
#include <stdio.h>

int main() {


    // 创建一个子进程，在子进程中执行exec函数族中的函数
    pid_t pid = fork();

    if(pid > 0) {
        // 父进程
        printf("i am parent process, pid : %d\n",getpid());
        // 如果不加这句，会存在孤儿进程，输出异常
        sleep(1);
    }else if(pid == 0) {
        // 子进程
        // 调用自己写的可执行程序
        // execl("hello","hello",NULL);

        // 调用系统进程
        execlp("ps", "ps", "aux", NULL); 

        //调用系统进程不需要
        perror("execl");
        printf("i am child process, pid : %d\n", getpid());

    }

    for(int i = 0; i < 3; i++) {
        printf("i = %d, pid = %d\n", i, getpid());
    }


    return 0;
}