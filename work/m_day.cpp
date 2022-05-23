#include "head.h"
class File
{
public:
    void readFile(char* filename)
    {
        int fd = open(filename, O_RDONLY);
        if (-1 == fd)
        {
            perror("open");
            return ;
        }
        close(fd);
    }
    
};
int main()
{
    char* filename = "1.txt";
    File test;
    test.readFile(filename);

    return 0;
}