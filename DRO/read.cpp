#include "read.h"
#include <iomanip>
// const string filePath = "/Users/zong/Code/unix/DRO/时差测量数据.csv";
const string filePath = "/Users/zong/Code/unix/DRO/20220617-4.csv";

// const string key = "EB9AC00D0200F9F9";
const string key = "eb9ac00d0200f9f9";
// std::string key = "EB9009F300000077";
//版本一
// void Read::Resplace(string &resTmp)
// {
//     int pos;
//     pos = resTmp.find("-");
//     while (pos != -1)
//     {
//         // str.length()求字符的长度，注意str必须是string类型
//         resTmp.replace(pos, string("-").length(), "");
//         pos = resTmp.find("-");
//     }

//     // cout << resTmp << endl;
// }
//版本2
void Read::Resplace(string &resTmp)
{
    int pos;
    pos = resTmp.find(" ");
    while (pos != -1)
    {
        // str.length()求字符的长度，注意str必须是string类型
        resTmp.replace(pos, string(" ").length(), "");
        pos = resTmp.find(" ");
    }

    // cout << resTmp << endl;
}
string tmpStr = "";
void Read::findKey(string key, vector<string> tmp, vector<string> &strResult, vector<string> &vectorResult, string &writeStr)
{
    for (int i = 0; i < tmp.size(); i++)
    {
        if (tmp[i] == key)
        {

            for (int j = 0; j < 64; j++)
            {

                if ((i + j) < tmp.size())
                    tmpStr = tmpStr + tmp[i + j];
                // vectorResult.push_back(tmp[i + j]);
                // vectorResult.push_back(tmp[]));
            }
            tmpStr = tmpStr.substr(120, 896);
            // cout<<tmpStr<<endl;

            writeStr += tmpStr;
            strResult.push_back(tmpStr);
            i = i + 64;
        }

        // strResult.push_back(tmpStr);
        // cout<<tmpStr;
        // for(int i = 0 ; i < tmpStr.size(); i+=8)
        //     {
        //         string tmp = tmpStr.substr(i,8);
        //         vectorResult.push_back(tmp);
        //         // cout<<tmpStr.substr(i,8)<<endl;
        //         cout<<tmp<<endl;
        //     }
        tmpStr.clear();
    }
    // cout<<writeStr<<endl;
    for (int i = 0; i < writeStr.size(); i += 16)
    {
        string tmp = writeStr.substr(i, 16);
        vectorResult.push_back(tmp);
        // cout<<tmpStr.substr(i,8)<<endl;
        // cout<<tmp<<endl;
    }
}

vector<string> Read::readData(string filePath, string &resTmp)
{
    vector<string> res;

    ifstream ifs;
    ifs.open(filePath, ios::in);
    if (!ifs.is_open())
    {
        cout << "Error: Could not open" << endl;
    }
    vector<string> item;       //用于存放文件中的一行数据
    string temp;               //临时存储文件中的一行数据
    while (getline(ifs, temp)) //利用 getline（）读取文件中的每一行，并放入到 item 中
    {
        item.push_back(temp);
    }
    //遍历文件中的每一行数据
    for (auto it = item.begin(); it != item.end(); it++)
    {
        string str;
        //其作用是把字符串分解为单词(在此处就是把一行数据分为单个数据)
        istringstream istr(*it);
        //将字符串流 istr 中的字符读入到 str 字符串中，读取方式是以逗号为分隔符,具体是哪一列需要先打开csv文件看一下
        for (int i = 0; i < 21; i++)//16
            getline(istr, str, ',');
        Resplace(str); //去除数据中的连接符号等等
        str = str.substr(0, 16);
        res.push_back(str);
        resTmp += str;
    }

    return res;
}

void Read::Channel(vector<string> test, vector<double> &Channel_A, vector<double> &Channel_B, vector<double> &Channel_C, vector<double> &Channel_D)
{
    for (int i = 0; i < test.size(); i++)
    {
        string tmp = test[i].substr(0, 1);
        int intTmp = stoi(tmp, nullptr, 16);
        double res = calculate(test[i]);
        if ((intTmp & 2) == 2)
            Channel_A.push_back(res);
        if ((intTmp & 1) == 1)
            Channel_B.push_back(res);
        if ((intTmp & 3) == 3)
            Channel_C.push_back(res);
        if ((intTmp | 0) == 0)
        
            Channel_D.push_back(res);
    }
}
double Read::calculate(string test)
{
    double tmp;
    double tmpBig;
    double tmpSmall;
    tmpBig = stol(test.substr(1, 5), nullptr, 16) * 7.00000;
    tmpSmall = stol(test.substr(6, 10), nullptr, 16) / 1e9 / 1.2 / 64;
    tmp = tmpSmall + tmpBig;

    return tmp;
}

void toEight(string tmp, vector<string> &tmpRes)
{
    for (int i = 0; i < tmp.size(); i += 8)
    {
        string tmp_new = tmp.substr(i, 8);
        tmpRes.push_back(tmp_new);
        // cout<<tmpStr.substr(i,8)<<endl;
        cout << tmp << endl;
    }
}

int main()
{
    ofstream outfile("C.txt", ios::trunc);
    string writeStr = "";
    vector<string> vectorResult;
    vector<string> result;
    vector<string> strResult;
    vector<string> res;
    string flag = "";
    string resTmp;
    Read test;
    result = test.readData(filePath, resTmp);

    cout << result.size() << endl;

    test.findKey(key, result, strResult, vectorResult, writeStr);

    vector<double> Channel_A, Channel_B, Channel_C, Channel_D;
    test.Channel(vectorResult, Channel_A, Channel_B, Channel_C, Channel_D);
    cout << Channel_A.size() << endl;
    for (auto i : Channel_C)
    {
        // outfile<<"B:"<<i<<endl;
        outfile << "C:" << fixed << setprecision(12) << i << endl;
        // cout<<i;
    }
    outfile.close();
    cout << vectorResult.size() << endl;

    cout << strResult[1] << endl;
    cout << strResult.size() << endl;
    cout << writeStr.size() << endl;


    return 0;
}