#include <iostream>  
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>  
  
using namespace std;  
  
  
int main()  
{  
    // 写文件  
    ofstream outFile;  
    outFile.open("data.csv", ios::out); // 打开模式可省略  
    outFile << "name" << ',' << "age" << ',' << "hobby" << endl;  
    outFile << "Mike" << ',' << 18 << ',' << "paiting" << endl;  
    outFile << "Tom" << ',' << 25 << ',' << "football" << endl;  
    outFile << "Jack" << ',' << 21 << ',' << "music" << endl;  
    outFile.close();  
  
    // 读文件  
    ifstream inFile("data.csv", ios::in);  
    string lineStr;  
    vector<vector<string>> strArray;  
    while (getline(inFile, lineStr))  
    {  
        // 打印整行字符串  
        cout << lineStr << endl;  
        // 存成二维表结构  
        stringstream ss(lineStr);  
        string str;  
        vector<string> lineArray;  
        // 按照逗号分隔  
        while (getline(ss, str, ','))  
            lineArray.push_back(str);  
        strArray.push_back(lineArray);  
    }  
      
    getchar();  
    return 0;  
}  

