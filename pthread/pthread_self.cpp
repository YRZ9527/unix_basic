#include "head.h"


//指定链接线程库

int main()
{

    pthread_t tid = 0;
    tid = pthread_self();

    cout<<"tid = "<<tid<<endl;
    if(pthread_equal(tid, pthread_self()))
    {
        cout<<"same id"<<endl;
    }
    else 
    {
        cout<<"different id"<<endl;
    }
}