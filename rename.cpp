#include "head.h"


int main() {
    
    int ret = rename("1.txt","new_1.txt");
    

    if(ret == -1)
    {
        perror("mkdir_test");
        return -1;
    }


    return 0;

}