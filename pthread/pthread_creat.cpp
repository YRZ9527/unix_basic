#include "head.h"

void *fun(void *arg)
{
    cout<<"new pthread "<<pthread_self()<<"\n";
    return NULL;
}
int main(int argc, char **argv)
{
    int ret = -1;
    pthread_t tid = -1;

    ret = pthread_create(&tid, NULL,fun,NULL);
    if(0 != ret)
    {
        cout<<"pthread create failed"<<endl;
        return 1;
    }
    cout<<"main pthread tid"<<pthread_self()<<endl;

    cout<<"--------------------------------"<<endl;
    cout<<"按下任意键退出"<<endl;
    getchar();
    return 0;

    return 0;
}