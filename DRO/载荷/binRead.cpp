#include "iostream"
#include "vector"
#include "memory"
#include "fstream"
using namespace std;
const string filePath = "DRO/载荷/test.dat";

/// C++ 读取bin文件
int getBinSize(std::string path)
{
    int size = 0;
    std::ifstream infile(path, std::ifstream::binary);

    infile.seekg(0, infile.end);
    size = infile.tellg();
    infile.seekg(0, infile.beg);

    infile.close();
    cout << size << endl;
    // printf("\npath=%s,size=%d \n", path, size);
    return size;
}

void readBin(std::string path, char *buf, int size)
{
    std::ifstream infile(path, std::ifstream::binary);
    // std::ifstream infile(path, ios::in);

    // infile.read(static_cast<char *>(buf), size);
    infile.read(buf, size);
    infile.close();
}

/// C++ 保存bin文件
void writeBin(std::string path, char *buf, int size)
{
    std::ofstream outfile(path, std::ifstream::binary);

    outfile.write((char *)(buf), size);

    outfile.close();
}

int main()
{
    // read binFile
    std::string filePath = "/Users/zong/Code/unix/DRO/载荷/test.dat";
    int size = getBinSize(filePath);
    cout<<size<<endl;
    char *buf = new char[size];
    readBin(filePath, buf, size);
    for(int i = 0; i < 10; i++)
    {
        buf[i] = (unsigned char) buf[i];
        buf[i] = (unsigned int) buf[i];
        cout<<(buf[i])<<endl;
    }
    // float *fbuf = reinterpret_cast<float *>(buf);

    // // write binFile
    // std::string saveFilePath = "./demo_saved.bin";
    // writeBin(saveFilePath, buf, size);

    // delete[] buf;

    return 0;
}






 
// #include <fstream>
// #include <iostream>
// using namespace std;
// int main()
// {    
//     ifstream in("/Users/zong/Code/unix/DRO/载荷/test.dat");
//     int n[30000];
//     size_t count = 0;    
//     char buf[4] = {0};
//     unsigned int t;
 
//     while (1)
//     {
//         in.read(buf, 2);
 
//         t = buf[1];//存储时高位在后。
//         t <<= 8;
//         t |= buf[0];
//         n[count] = t;
//         count++;
//     }
//     in.close();
//     for (size_t i = 0; i < count; i++)
//     {
//         cout << n[i] << "\t";
//         if ((i + 1) % 8 == 0)
//             cout << endl;
//     }
//     cout << endl;
//     return 0;
// }
