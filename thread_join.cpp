#include<iostream>
#include<stdlib.h>
#include <string>
#include <pthread.h>
#include  "head.h"
using namespace std;
void *fun(void *arg)
{
  for(auto i = 0; i < 5; i++)
  {
    cout<<"fun running"<<endl;
    cout<<i<<endl;
    sleep(1);
  }
  return (void *)0x3;
}

int main()
{
  int ret = -1;
  void *retp = NULL;
  pthread_t tid;
  ret = pthread_create(&tid,NULL,fun,NULL);

  if(0 != ret)
  {
    cout<<"pthread created failed"<<endl;
    return 1;
  }
  cout<<"main pthread running"<<endl;
//等待函数会阻塞
//


  ret = pthread_join(tid,&retp);
  if(0 != ret)
  {
    cout<<"pthread join failed"<<endl;
    return 1;
  }
  cout<<retp<<endl;
  cout<<"main exit"<<endl;

  return 0;

}
