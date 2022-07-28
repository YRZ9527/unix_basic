#include"write.h"
#include"read.h"
#include"memory"

//二进制写出
#include <iostream>
#include <fstream>
using namespace std;


// void Write::writeFile(const string filename, vector<string> &wrietTmp)
// {
    

// }

// void Write::display()
// {

}
// class CStudent
// {
// public:
//     char szName[20];
//     int age;
// };
// int main()
// {
//     CStudent s;       
//     ifstream inFile("/Users/zong/Code/SLR_Work/DRO/test1.bin",ios::in|ios::binary); //二进制读方式打开
//     if(!inFile) {
//         cout << "error" <<endl;
//         return 0;
//     }
//     while(inFile.read((char *)&s, sizeof(s))) { //一直读到文件结束
//         cout << s.szName << " " << s.age << endl;   
//     }
//     inFile.close();
//     return 0;
// }


class CStudent
{
public:
    char szName[20];
    int age;
};
int main()
{
    CStudent s;
    ofstream outFile("students.dat", ios::out | ios::binary);
    while (cin >> s.szName >> s.age)
        outFile.write((char*)&s, sizeof(s));
    outFile.close();
    return 0;
}
