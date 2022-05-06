#include "head.h"

int main() {
    int ret1 = access("1.txt",F_OK);
    if (ret1 == -1){
        perror("access");
    }
    int ret2 = access("1.txt",R_OK);
    if(ret2 == -1)               
    {



        perror("run error");
    }
    
    return 0;
}
