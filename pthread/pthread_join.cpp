#include "head.h"

void* myWork(void* arg) {
    cout<<"child pthread"<<endl;
    cout<<"num = "<<(int*)arg<<endl;
    cout<<"child pthread id"<<pthread_self()<<endl;
    val++;
    pthread_exit((void *)&val);

int main() {
    


    return 0;
}