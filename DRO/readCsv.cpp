#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
const string filePath = "/Users/zong/Code/SLR_Work/DRO/20220629-14 3.csv";
const string outPath = "test.bin";
string tmp_str = "";

void writeFile(string outputFilename, vector<string> data)
{
	string filePath = outputFilename;
	ofstream outFile(filePath,ios::out | ios::binary);
}

void readFile(string& originalStr )
{
	vector<string> data;
	ifstream ifs;
	ifs.open(filePath,ios::in);
	if(!ifs.is_open())
	{
		cout<<"Error: Could not open"<<endl;
		return ;
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
		//其作用是把字符串分解为单词(在此处就是把一行数据分为单个数据)
		istringstream istr(*it);                 
		//将字符串流 istr 中的字符读入到 str 字符串中，读取方式是以逗号为分隔符 
		for(int i=0; i < 21; i++)
			getline(istr, str, ',');                 
		// getline(istr, str, ',');                    
		// cout << str << "\t";            // str 对应第二列数据 
		data.push_back(str);
		originalStr += str;	
	}   
}

void getData(string data)
{
	if(data.size())
	{
		for(auto i = 0; i < data.size(); i++)
		{
			int tmp = data[i] + data [i+1];

		}


	}
}
 
int main()
{
	vector<string> data;
	string tmp = "";
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
		//其作用是把字符串分解为单词(在此处就是把一行数据分为单个数据)
		istringstream istr(*it);                 
		//将字符串流 istr 中的字符读入到 str 字符串中，读取方式是以逗号为分隔符 
		for(int i=0; i < 21; i++)
			getline(istr, str, ',');                 
		// getline(istr, str, ',');                    
		// cout << str << "\t";            // str 对应第二列数据 
		data.push_back(str);
		
		tmp += str;
		
	}   
	// cout<<data.size()<<endl;
	// cout<<data[1]<<endl;
	cout<<tmp<<endl;
	return 0;
}

