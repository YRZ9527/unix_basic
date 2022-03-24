#include "head.h"

int main()
{


    pid_t pid = fork();
    if(pid > 0){
        cout<<"i am a parent process"<<"pid ="<<getpid()<<","<<"ppid=:"<<getppid()<<endl;
    
    } else if(pid == 0)
    {
        sleep(1);

        cout<<"i am a child process"<<"pid ="<<getpid()<<","<<"ppid=:"<<getppid()<<endl;

    }
    for(int i=0; i < 3; i++)
    {
       printf("i : %d , pid : %d\n", i , getpid()); 
    }

    return 0;
}