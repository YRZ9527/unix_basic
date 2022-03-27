#include "head.h"

int main()
{

    int pipefd[2];
    int ret = pipe(pipefd);
    if (-1 == ret)
    {
        perror("pipe");
        exit(0);
    }

    pid_t pid = fork();

    if (pid > 0)
    {
        cout << "parent process" << getpid() << endl;
        char buf[1024] = {0};

        while (1)
        {

            int len = read(pipefd[0], buf, sizeof(buf));
            printf("parent recv : %s, pid : %d\n", buf, getpid());
        }
    }

    if (pid == 0)
    {
        cout << "child process" << getpid() << endl;
    }

    return 0;
}