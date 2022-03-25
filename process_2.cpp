#include "head.h"

int main() {

    pid_t pid;

    for(int i = 0; i < 5; i++) {

        pid = fork();
        if(pid == 0) {
            break;
        }
    }

    if(pid > 0) {
        while(1) {

            cout<<"parent,pid"<<getpid()<<endl;

            int st;
            int ret = wait(&st);
            if(ret == -1) {
                break;
            }

            if(WIFEXITED(st)) {
                cout<<"退出的状态码"<<WEXITSTATUS(st)<<endl;
            }
            if(WIFSIGNALED(st)) {
                cout<<"被哪个信号干掉了"<<WTERMSIG(st)<<endl;
            }

            cout<<"child die"<<""<<getpid()<<endl;
            sleep(1);
        }
    }
    else if(pid == 0)
    {
        while(1) {
            cout<<"child,pid = "<<getpid()<<endl;
            sleep(1);
        }
        exit(0);
    }

    return 0;
}