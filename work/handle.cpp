#include "handle.h"

int Init::getSize()
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
    fin.close();
    return lineCnt + 1;
}

File::File(vector<vector<int>> &temp, char *path, int size)
{
    ifstream infile;
    infile.open(path);
    for (int i = 0; i < size; i++) //定义行循环
    {
        for (int j = 0; j < 3; j++) //定义列循环
        {
            infile >> temp[i][j]; //读取一个值（空格、制表符、换行隔开）就写入到矩阵中，行列不断循环进行
        }
    }
    infile.close(); //读取完成之后关闭文件
}

void File::hoursResult(vector<vector<int>> temp, vector<int> &monthRes, int size)
{
    for (int month = 0; month <= 12; month++)
    {
        for (int i = 0; i <= size; i++)
        {
            if (temp[i][1] == month + 1)
            {
                monthRes[month]++;
            }
        }
    }
}
void File::nonRepeatResult(vector<vector<int>> data, vector<int> &nonRepeatResult, int size)
{
    set<int> res1, res2, res3, res4, res5, res6, res7, res8, res9, res10, res11, res12;

    // vector<set<int>> setTest;
    // setTest.push_back(res1);
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
    nonRepeatResult.push_back(res1.size());
    nonRepeatResult.push_back(res2.size());
    nonRepeatResult.push_back(res3.size());
    nonRepeatResult.push_back(res4.size());
    nonRepeatResult.push_back(res5.size());
    nonRepeatResult.push_back(res6.size());
    nonRepeatResult.push_back(res7.size());
    nonRepeatResult.push_back(res8.size());
    nonRepeatResult.push_back(res9.size());
    nonRepeatResult.push_back(res10.size());
    nonRepeatResult.push_back(res11.size());
    nonRepeatResult.push_back(res12.size());
}
template <typename T>
void display(vector<T> monthRes, vector<T> nonRepeatResult)
{
    for (auto i = monthRes.begin(); i != monthRes.end(); i++)
    {

        cout << *i << " ";
    }
    cout << endl;
    for (auto i = nonRepeatResult.begin(); i != nonRepeatResult.end(); i++)
    {

        cout << *i << " ";
    }
}
template <typename T>
void writeFile(char *outPath, vector<T> month, vector<T> repeatRes)
{
    string topic = "2024年1～5月，2023年6～12月";
    ofstream outfile(outPath, ios::app);
    // outfile<<topic<< endl;
    for (int i = 0; i < 12; i++)
    {
        outfile << repeatRes[i] << "天"
                << month[i] << "小时"
                << " ";
        ;
    }
    outfile<<endl;
}
// template<typename T>
// void writeFile(string pathname[],vector<T> month,vector<T> repeatRes)
// {
//     string topic = "2024年1～5月，2023年6～12月";

//     outfile<<topic<< endl;
// }

int main()
{
    //vector<char *> pathname = {"1_0.74.txt", "1_1.txt", "1_1.4.txt", "2_0.74.txt", "2_1.txt", "2_1.4.txt", "3_0.74.txt", "3_1.txt", "3_1.4.txt", "4_0.74.txt", "4_1.txt", "4_1.4.txt", "5_0.74.txt", "5_1.txt", "5_1.4.txt"};
    char *path = "1.1.txt";
    char *outPath = "out.txt";
    vector<int> monthRes(12, 0);
    vector<int> nonRepeatResult;
    vector<vector<int>> temp(3000, vector<int>(3));
    Init test(path);
    int size = test.getSize();
    // cout << "size = " << size << endl;
    File file(temp, path, size);
    file.hoursResult(temp, monthRes, size);
    file.nonRepeatResult(temp, nonRepeatResult, size);
    for (int i = 0; i < 12; i++)
    {
    }
    writeFile(outPath, monthRes, nonRepeatResult);
    return 0;
}