#include "head.h"
#include "dirent.h"


int main(int argc, char *argv[])
{
    if(argc < 2){
        cout<<"path"<<argv[0]<<endl;
        return -1;
    }


    int num = GetFileNum(argv[1]);
    return 0;
}