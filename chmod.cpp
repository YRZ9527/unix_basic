#include"head.h"

int main() {
    int res1 = access("/Users/zong/Code/tsy",F_OK);
    if(res1 == -1) {
        perror("access");
        return -1;
    }
    int ret = chmod("/Users/zong/Code/tsy",0777);
    if(ret == -1)
    {
        perror("chmod");
        return -1;
    }
    return 0;
}