#include "head.h"


int main() {
    

    int ret = mkdir("mkdir_test",0777);
    if(ret == -1)
    {
        perror("mkdir_test");
        return -1;
    }
    int ret2 = rmdir("mkdir_test");

    return 0;

}