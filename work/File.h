#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <set>
using namespace std;

set<int> res1;
set<int> res2;
set<int> res3;
set<int> res4;
set<int> res5;
set<int> res6;
set<int> res7;
set<int> res8;
set<int> res9;
set<int> res10;
set<int> res11;
set<int> res12;

class Size
{
public:
    int getSize(char *path);
};
int Size::getSize(char *path)
{
    int size;
    ifstream fin(path, ios::in);
    if (!fin)
    {
        cerr << "can not open file" << endl;
        return -1;
    }
    char c;
    int lineCnt = 0;
    while (fin.get(c))
    {
        if (c == '\n')
            lineCnt++;
    }
    // cout<<"lineCnt = "<<lineCnt + 1<<endl;
    fin.close();
    return lineCnt + 1;
    ;
}
class File
{
private:
public:
    File(char *path, int size);
    ~File();
};
vector<vector<int>> data(2000, vector<int>(3));
File::File(char *path, int size)
{

    
    ifstream infile;               //定义读取文件流，相对于程序来说是in
    infile.open(path);             //打开文件
    for (int i = 0; i < size; i++) //定义行循环
    {
        for (int j = 0; j < 3; j++) //定义列循环
        {
            infile >> data[i][j]; //读取一个值（空格、制表符、换行隔开）就写入到矩阵中，行列不断循环进行
        }
    }
    infile.close(); //读取完成之后关闭文件

    vector<string> res2023;
    vector<int> monthRes(12, 0);
    vector<int> monthRes2024(12, 0);

    for (int month = 1; month <= 12; month++)
    {
        for (int i = 0; i <= size; i++)
        {
            if (data[i][0] == 2023 && data[i][1] == month)
            {
                // repeatRes[month].insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
                monthRes[month]++;
            }
            if (data[i][0] == 2024 && data[i][1] == month)
            {
                monthRes2024[month]++;
            }
        }
    }

    //res2023.push_back(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    //result.push_back(res2023);
    for (auto i = monthRes.begin(); i != monthRes.end(); i++)
    {

        cout << *i <<",";
    }
    cout << "2024year:" << endl;
    for (auto i = monthRes2024.begin(); i != monthRes2024.end(); i++)
    {

        cout << *i <<";";
    }
    for (auto i = res2023.begin(); i != res2023.end(); i++)
    {

        cout << *i << endl;
    }
    cout << res2023.size() << endl;

    // for (int i = 0; i <= size; i++)
    // {
    //     if (data[i][1] == 1)
    //         res1.insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    //     if (data[i][1] == 2)
    //         res2.insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    //     if (data[i][1] == 3)
    //         res3.insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    //     if (data[i][1] == 4)
    //         res4.insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    //     if (data[i][1] == 5)
    //         res5.insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    //     if (data[i][1] == 6)
    //         res6.insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    //     if (data[i][1] == 7)
    //         res7.insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    //     if (data[i][1] == 8)
    //         res8.insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    //     if (data[i][1] == 9)
    //         res9.insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    //     if (data[i][1] == 10)
    //         res10.insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    //     if (data[i][1] == 11)
    //         res11.insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    //     if (data[i][1] == 12)
    //         res12.insert(to_string(data[i][0]) + to_string(data[i][1]) + to_string(data[i][2]));
    // }





      for (int i = 0; i <= size; i++)
    {
        if (data[i][1] == 1)
            res1.insert(data[i][2]);
        if (data[i][1] == 2)
            res2.insert(data[i][2]);
        if (data[i][1] == 3)
            res3.insert(data[i][2]);
        if (data[i][1] == 4)
            res4.insert(data[i][2]);
        if (data[i][1] == 5)
            res5.insert(data[i][2]);
        if (data[i][1] == 6)
            res6.insert(data[i][2]);
        if (data[i][1] == 7)
            res7.insert(data[i][2]);
        if (data[i][1] == 8)
            res8.insert(data[i][2]);
        if (data[i][1] == 9)
            res9.insert(data[i][2]);
        if (data[i][1] == 10)
            res10.insert(data[i][2]);
        if (data[i][1] == 11)
            res11.insert(data[i][2]);
        if (data[i][1] == 12)
            res12.insert(data[i][2]);
    }
    // for (auto i = res3.begin(); i != res3.end(); i++)
    // {

    //     cout << *i << endl;
    // }
    cout<<"重复天数"<<endl;
    cout<<res6.size()<<","<<res7.size()<<","<<res8.size()<<","<<res9.size()<<","<<res10.size()<<","<<res11.size()<<","<<res12.size()<<","<<res1.size()<<","<<res2.size()<<","<<res3.size()<<","<<res4.size()<<","<<res5.size()<<endl;
}

File::~File()
{
}
// for (int i = 0; i < 25; i++)
// 	{
// 		outfile  << I[i][0] << "    " << I[i][1] << "    " 
//             << str[i][0] << "    " << str[i][1] << "    "
// 			<< str[i][2] << "    " << str[i][3]<< endl;
// 	};
 
// 	myfile.close();
// 	outfile.close();
// }