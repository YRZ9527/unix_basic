// #include"write.h"
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


void WriteBin(string tmp,const string path)
{
    ofstream outFile(path,ios::out | ios::binary);
    for(int i = 0; i < tmp.size(); i++)
    {
        
        outFile.write(reinterpret_cast<char *>(int(tmp[i]), sizeof(tmp[i]));
    }
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
//     ofstream outFile("students.dat", ios::out | ios::binary);
//     while (cin >> s.szName >> s.age)
//         outFile.write((char*)&s, sizeof(s));
//     outFile.close();
//     return 0;
// }


int main(int argc, char** argv)
{
    string test = "44555";
    const string path = "student.bin";
    WriteBin(test,path);
    return 0;
}
