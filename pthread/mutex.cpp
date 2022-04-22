#include<iostream>
#include<string>
#include<unistd.h>
#include<stdio.h>
using namespace std;
pthread_mutex_t mutex;

void* fun1(void* arg){

	int i = 0;
    pthread_mutex_lock(&mutex);
    for(i = 'A'; i < 'Z'; i++){
        putchar(i);
        fflush(stdout);
    }
    pthread_mutex_unlock(&mutex);
    return nullptr;
}

void* fun2(void* arg){
    int i = 0;
    pthread_mutex_lock(&mutex);
    for(i = 'a'; i < 'z'; i++){
        putchar(i);
        fflush(stdout);
    }
    pthread_mutex_unlock(&mutex);
    return nullptr;
}



int main() {
    int ret = -1;
    ret = pthread_mutex_init(&mutex, NULL);
    if(0 != ret) {
        cout<<"ERROR: pthread_mutex_init "<<endl;
        return 1;
    }
	pthread_t tid1,tid2;
	int num = 10;
	int ret1 = pthread_create(&tid1,NULL,fun1,(void*)&num);
    int ret2 = pthread_create(&tid2,NULL,fun2, (void*)&num);
	// if(ret != 0) {

	// 	char * errstr = strerror(ret);
	// 	cout<<"error: s%\n"<<errstr;
	// }
    pthread_join(tid1,nullptr);
    pthread_join(tid2,nullptr);

    pthrread_mutex_destroy(&mutex);


	sleep(1);
    cout<<"main pthread exit"<<endl;
	return 0;
}
