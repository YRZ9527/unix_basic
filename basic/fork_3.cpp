#include"head.h"
int var = 88;
//读时共享，写时拷贝
int main() {
    
    pid_t pid = -1;

    pid = fork();

    if(pid == -1) {
        perror("fork");
        return 1;
    }

    if(pid == 0) {
        //子进程
        sleep(1);

        cout<<"child process"<<var<<endl;
        
        
    }
    else{
        //父进程
        cout<<"parent process"<<var<<endl;
        var++;
        cout<<"parent process"<<var<<endl;

    }
    return 0;
}