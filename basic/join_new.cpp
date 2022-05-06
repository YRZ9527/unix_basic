#include "head.h"
using namespace std;

void *fun1(void *arg)
{
    int i = 0;
    for(i = 'A'; i < 'Z'; i++)

    {
        putchar(i);
        fflush(stdout);
        usleep(100000);
    }
    return nullptr;
}

void *fun2(void *arg)
{
    int i = 0;
    for(i = 'z'; i > 'a'; i--)

    {
        putchar(i);
        fflush(stdout);
        usleep(100000);
    }
    return nullptr;
}

int main(int argc, char** argv)
{
    pthread_t tid1,tid2;

    pthread_create(&tid1, nullptr,fun1,nullptr);
    pthread_create(&tid2, nullptr,fun2,nullptr);
    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    cout<<endl;
    cout<<"main thread exit"<<endl;

}