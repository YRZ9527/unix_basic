/*
chatB
1. 读、写数据分开，用两个管道
    1. fifo1用于进程A写及进程B读
    2. fifo2用于进程B写及进程A读
2. 连续发送及接收信息，使用两个进程
    1. 父进程用于写数据
    2. 子进程用于读数据
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    // 判断写管道是否存在，不存在则创建
    int ret = access("fifo1", F_OK);
    if (ret == -1) {
        printf("fifo1不存在，创建...\n");
        ret = mkfifo("fifo1", 0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(-1);
        }
    } 

    // 判断读管道是否存在，不存在则创建
    ret = access("fifo2", F_OK);
    if (ret == -1) {
        printf("fifo2不存在，创建...\n");
        ret = mkfifo("fifo2", 0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(-1);
        }
    } 
    // 创建进程
    pid_t pid = fork();
    char buf[1024] = { 0 };
    if (pid > 0) {
        // 父进程
        // 打开写管道
        // 打开一次，否则系统可能会崩
        int fdw = open("fifo2", O_WRONLY);
        while (1) {
            // 从键盘读取输入
            printf("[chatB]please input: \n");
            fgets(buf, sizeof(buf), stdin);
            write(fdw, buf, strlen(buf));
            // 清空数组
            memset(buf, 0, sizeof(buf));
        }
        close(fdw);
    } else if (pid == 0) {
        // 子进程
        // 打开读管道
        // 打开一次，否则系统可能会崩
        int fdr = open("fifo1", O_RDONLY);
        while (1) {
            char buf[1024];
            int len = read(fdr, buf, sizeof(buf));
            if(len == 0) {
                printf("[chatB]写端断开连接了...\n");
                break;
            }
            printf("[chatB]recv : %s", buf);
            // 清空数组
            memset(buf, 0, sizeof(buf));
        }
        close(fdr);
    } else {
        perror("fork");
        exit(-2);
    }

    return 0;
}