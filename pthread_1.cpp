#include<iostream>
#include<string>
#include<unistd.h>
#include<stdio.h>
using namespace std;

void* myWork(void* arg){

	cout<<"child thread"<<endl;
	cout<<"num = d%\n"<<*(int*)arg;
	return NULL;
}



int main() {

	pthread_t tid;
	int num = 10;
	int ret = pthread_create(&tid,NULL,myWork,(void*)&num);
	if(ret != 0) {

		char * errstr = strerror(ret);
		cout<<"error: s%\n"<<errstr;
	}

	for(int i = 0; i < 5; i++){

		cout<<i<<endl;
	}

	sleep(1);
	return 0;
}
