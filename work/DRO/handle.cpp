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
        for (int j = 0; j < 14; j++) //定义列循环
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
void writeFile(char *outPath, vector<T> month)
{
    string topic = "2024年1～5月，2023年6～12月";
    ofstream outfile(outPath, ios::app);
    // outfile<<topic<< endl;
    for (int i = 0; i < 12; i++)
    {
        outfile << month[i] << "小时"
                << " ";
        ;
    }
    outfile<<endl;
}

int main()
{
    
    char *path = "DRO.txt";
    char *outPath = "out.txt";
    vector<int> monthRes(12, 0);
    vector<int> nonRepeatResult;
    vector<vector<int>> temp(3000, vector<int>(3));
    Init test(path);
    int size = test.getSize();
    cout<<size<<endl;

    return 0;
}