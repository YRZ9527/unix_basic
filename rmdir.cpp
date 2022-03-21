#include "head.h"


int main() {
    
    int ret = rmdir("mkdir_test");
    if(ret == -1)
    {
        perror("mkdir_test");
        return -1;
    }


    return 0;

}