#include "head.h"

int main() {



    int ret = access("fifo1",F_OK);
    if(ret == -1){
        cout<<"fifo not exist"<<endl;
        ret  = mkfifo("fifo1",0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(-1);
        }
    }

    ret = access("fifo2", F_OK);
    if (ret == -1) {
        printf("fifo2不存在，创建...\n");
        ret = mkfifo("fifo2", 0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(-1);
        }
    } 


    pid_t pid = fork();
    char buf[1024];

    if(pid > 0) {


        //父进程
        int fdw = open("fifo1", O_WRONLY);
        while(1){

            cout<<"please input"<<endl;
            fgets(buf, sizeof(buf),stdin);
            write(fdw,buf, sizeof(buf));
            memset(buf, 0, sizeof(buf));
        }
        close(fdw);
    }
    else if(pid == 0)
    {
        int fdr = open("fifo1", O_RDONLY);
        while(1){

            char buf[1024];
            int len = read(fdr, buf, sizeof(buf));
            if(len == 0)
            {
                cout<<"connect error"<<endl;
                break;
            }
            cout<<"chat recv: %s"<<buf<<endl;


            memset(buf, 0, sizeof(buf));
        }
        close(fdr);
    }
    else{
        perror("fork");
        exit(-2);
    }
    return 0;
}