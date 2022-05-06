#include "head.h"


int main() {

// create a fork
    pid_t pid = fork();

    if(pid > 0){
        cout<<"parent process , pid :"<<pid<<endl;
        sleep(1);

    }

    else if(pid == 0){
        char* envp[] = {"~/Code/unix",NULL};
        execle("../unix","hello",NULL,envp);
        perror("execle");
        cout<<"child process"<<":"<<getpid()<<endl;
    }

    for(int i=0; i< 3; i++)
    {
        cout<<"i="<<i<<"->"<<getpid()<<endl;
    }
    

    return 0;
}