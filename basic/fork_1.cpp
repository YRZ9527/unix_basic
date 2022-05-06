#include "head.h"

int main() {   

    //pid_t pid = fork();


    cout<<"parent: "<<getppid()<<endl;

    cout<<"child: "<<getpid()<<endl;

    cout<<"group: "<<getpgid(getpid())<<endl;
    


    return 0;
}