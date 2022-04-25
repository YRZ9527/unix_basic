#include "head.h"

//线程互斥量变量
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void *fun1(void *arg)
{
    //线程一先申请资源一、再申请资源二
    pthread_mutex_lock(&mutex1);
    cout<<"线程1加锁资源1ok"<<endl;
    pthread_mutex_lock(&mutex2);
    cout<<"线程1加锁资源2ok"<<endl;
    cout<<"线程一执行临界区代码"<<endl;
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return nullptr;

}


void *fun2(void *arg)
{
    //线程2先申请资源二，再申请资源一
     pthread_mutex_lock(&mutex2);
     cout<<"线程2加锁资源一"<<endl;
    pthread_mutex_lock(&mutex1);
    cout<<"线程2加锁资源一"<<endl;
    cout<<"线程二执行临界区代码"<<endl;
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    return nullptr;
}
int main()
{
    int ret = -1;


    pthread_t tid1,tid2;
    //初始化互斥量
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_create(&tid1,nullptr,fun1,nullptr);
    pthread_create(&tid2,nullptr,fun2,nullptr);

    ret = pthread_join(tid1,nullptr);
    if(ret != 0)
    {
        cout<<"Error: pthread_join failed"<<endl;
        return 1;
    }
    ret = pthread_join(tid2,nullptr);
    if(ret != 0)
    {
        cout<<"Error: pthread_join failed"<<endl;
        return 1;
    }
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
}