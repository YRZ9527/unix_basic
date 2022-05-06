#include "head.h"
using namespace std;


void *fun(void* arg) {
    int i = 0;
    for(int i = 0; i < 5; i++) {
        cout<<"pthread do working"<<i<<endl;
        sleep(1);
    }
    //return nullptr;
    pthread_exit(nullptr);
}


int main(int argc, char** argv)
{
    int ret = -1;
    pthread_t tid;
    ret = pthread_create(&tid,nullptr,fun,nullptr);
    if(0 != ret)
    {
        cout<<"pthread created error: "<<endl;
        return 1;
    }

    cout << "main thread started"<<pthread_self()<<endl;
    //设置线程分离  
    ret = pthread_detach(tid);
    if(0 != ret)
    {
        cout<<"pthread detach error: "<<endl;
        return 1;

    }
    ret = pthread_join(tid, NULL);
    if(0 != ret)
    {
        cout<<"pthread join error: "<<endl;
    } else {
        cout<<"pthread join success: "<<endl;
    }
    cout<<"any key to exit"<<endl;
    getchar();
}

//进程退出，子线程结束，所有子线程共用线程的资源
//处于分离状态的线程不能被join
