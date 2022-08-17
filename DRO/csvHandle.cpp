#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
 
using namespace std;
const string path  =  'test.bin'

void readFile(string path)
 
int main()
{
	//读取文件中的数据
	ifstream ifs;							//创建流对象
	ifs.open("/Users/zong/Code/SLR_Work/DRO/data.csv", ios::in);	//打开文件
 
	if (!ifs.is_open())						//判断文件是否打开
	{
		cout << "打开文件失败！！！";
		return 0;
	}
	vector<string> item;		//用于存放文件中的一行数据
	string temp;				//临时存储文件中的一行数据
 
	while (getline(ifs, temp))  //利用 getline（）读取文件中的每一行，并放入到 item 中
	{
		item.push_back(temp);
	}
    
    //遍历文件中的每一行数据
	for (auto it = item.begin(); it != item.end(); it++)
	{
		string str;
        // cout<<*it<<endl;
 
		//其作用是把字符串分解为单词(在此处就是把一行数据分为单个数据)
		istringstream istr(*it);                 
		//将字符串流 istr 中的字符读入到 str 字符串中，读取方式是以逗号为分隔符 
		for(int i=0; i < 21; i++)
			getline(istr, str, ',');                 
          
 
		// getline(istr, str, ',');                    
		cout << str[0] << "\t";            // str 对应第二列数据 
    
	}    
 
	system("pause");
	return 0;
}

