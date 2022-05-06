#include"head.h"

int main() {
    struct stat statbuf;
    int ret = stat("1.txt",&statbuf);

    if(ret == -1) {
        perror("stat");
        return -1;
    }

    cout<<statbuf.st_size<<endl;
    cout<<statbuf.st_mode<<endl;
    cout<<statbuf.st_mtime<<endl;
    return 0;
}