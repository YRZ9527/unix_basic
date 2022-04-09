#include "head.h"

void* myWork(void* arg) {
    cout<<"child pthread"<<endl;
    cout<<"num = "<<(int*)arg<<endl;
    cout<<"child pthread id"<<pthread_self()<<endl;
    return NULL;
}
int main() 
{

    pthread_t tid;
    int num = 10;
    int ret = pthread_create(&tid,NULL,myWork,(void*)&num);
    if(ret != 0) 
    {
        cout<<"pthread_create error"<<strerror(ret) << std::endl;
    }
    cout<<"tid ="<<tid<<"   main pthread"<<pthread_self()<<endl;
    for(int i=0; i < 5; i++)
    {
        cout<<"i = "<<i<<endl;
    }
    pthread_exit(NULL);
    cout<<"test message"<<endl;
    return 0;
}