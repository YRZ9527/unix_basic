#include"head.h"


int main() {
    int num = 0;

    pid_t pid = fork();
    // create a fork

    if(pid > 0) {
        cout<<"pid:"<<pid<<endl;
        cout<<"i am parent process ,pid: "<<getpid()<<"ppid:"<<getppid()<<endl;
        cout<<"parent num:"<<num<<endl;

        num += 10;
        cout<<"parent num + 10:"<<num<<endl;
    } else if(pid == 0) {
        cout<<"i am child process ,pid: "<<getpid()<<"ppid:"<<getppid()<<endl;
        cout<<"child num:"<<num<<endl;

        num += 100;
        cout<<"child num + 100:"<<num<<endl;
    }
    for(auto i = 0; i < 3; i++) {
        printf("i : %d , pid : %d\n", i , getpid());
        sleep(1);
    }


    return 0;
}  