#include <stdio.h>
#include <pthread.h>

// 全局变量创建互斥量，保证所有线程都能访问
pthread_mutex_t mutex;

int total_tickets = 100;

void* selltickets(void* arg) {
    while (1) {
        // 加锁
        pthread_mutex_lock(&mutex);
        if (total_tickets > 0) {
            // 访问共享变量
            printf("线程%ld 正在售卖第%d张票\n", pthread_self(), total_tickets);
            total_tickets--;
        } else {
            // 解锁
            pthread_mutex_unlock(&mutex);
            break;
        }
        // 解锁
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main()
{
    // 初始化互斥量
    pthread_mutex_init(&mutex, NULL);

    // 创建三个线程
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;
    pthread_create(&tid1, NULL, selltickets, NULL);
    pthread_create(&tid2, NULL, selltickets, NULL);
    pthread_create(&tid3, NULL, selltickets, NULL);
    // 线程连接，回收子线程的资源，阻塞
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_exit(NULL);     // 退出main进程

    // 释放互斥量资源
    pthread_mutex_destroy(&mutex);
    return 0;
}