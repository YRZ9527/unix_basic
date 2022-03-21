#include "head.h"


int main() {
    
    int ret = truncate("1.txt",1111);
    if(ret == -1)
    {
        perror("turncate");
        return -1;
    }

    return 0;
}