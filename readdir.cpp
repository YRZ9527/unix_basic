#include "head.h"


int getFileNum(const char* path);

int main(int argc, char* argv[]) {
    if(argc < 2){
        cout<<"path"<<argv[0]<<endl;
        return -1;

    }
    int num = getFileNum(argv[1]);
    cout<<"File_Num:"<<num<<endl;
    



    return 0;
}

int getFileNum(const char* path)
{
    DIR *dir = opendir(path);

    if(dir == NULL)
    {
        perror("opendir");
        exit(0);
    }
    struct dirent *ptr = NULL;
    int total = 0;

    while((ptr = readdir(dir)) != NULL) {
        char *dname = ptr->d_name;
        if(strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0) {
            continue;
        }

        if(ptr->d_type == DT_DIR) {
            char newpath[256];
            cout<<"path"<<path<<"name:"<<dname<<endl;
            total += getFileNum(newpath);
        }
        if(ptr->d_type == DT_REG)
        {
            total ++;
        }
    }
    closedir(dir);
    return total;
}