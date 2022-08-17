#pragma once
#include<iostream>
#include<vector>
#include<deque>
#include<string>
#include<algorithm>
using namespace std;

#define ACCURACY 100;	//定义除法精度

class DividedByZeroException {	//定义除零错误
public:
	void error()
	{
		cout << "Divided By Zero Exception!" << endl;
	}
};

class WFloat	//高精度浮点数类
{
	//基本运算符重载
	friend WFloat operator+(const WFloat&, const WFloat&);	//加法重载
	friend WFloat operator-(const WFloat&, const WFloat&);	//减法重载
	friend WFloat operator*(const WFloat&, const WFloat&);	//乘法重载
	friend WFloat operator/(const WFloat&, const WFloat&) throw(DividedByZeroException);	//除法重载
	friend WFloat operator-(const WFloat&);	//负号重载

	//比较重载
	friend bool operator==(const WFloat&, const WFloat&);	//等于重载
	friend bool operator!=(const WFloat&, const WFloat&);	//不等于重载
	friend bool operator<(const WFloat&, const WFloat&);	//小于重载
	friend bool operator<=(const WFloat&, const WFloat&);	//小于等于重载
	friend bool operator>(const WFloat&, const WFloat&);	//大于重载
	friend bool operator>=(const WFloat&, const WFloat&);	//大于等于重载

	//扩展运算符重载
	friend WFloat operator+=(WFloat&, const WFloat&);	//加等重载
	friend WFloat operator-=(WFloat&, const WFloat&);	//减等重载
	friend WFloat operator*=(WFloat&, const WFloat&);	//乘等重载
	friend WFloat operator/=(WFloat&, const WFloat&);	//除等重载

	//输入输出重载
	friend ostream& operator<<(ostream&, const WFloat&);	//输出重载
	friend istream& operator>>(istream&, WFloat&);	//输入重载

public:
	WFloat();
	WFloat(int);	//用一个整数构造
	WFloat(string&);	//用一个字符串构造
	WFloat(const WFloat&);	//用一个高精度数构造
	WFloat operator=(const WFloat&);	//赋值函数
	WFloat abs() const;	//取绝对值
	~WFloat() {}

	static const WFloat ZERO;	//定义0
	static const WFloat ONE;	//定义1
	static const WFloat TEN;	//定义10（用于除法化整）

private:
	vector<char>integer;	//整数部分
	vector<char>decimal;	//小数部分
	void trim();	//将多余的零删去
	bool tag;	//用来表示正负，true为正
};

const WFloat WFloat::ZERO = WFloat(0);
const WFloat WFloat::ONE = WFloat(1);
const WFloat WFloat::TEN = WFloat(10);

void WFloat::trim()
{
	//因为我们是逆向存储的，所以整数的尾部和小数的首部可能会有多余的0
	vector<char>::reverse_iterator iter = integer.rbegin();	//对整数部分
	while (!integer.empty() && (*iter) == 0)
	{
		integer.pop_back();	//指向不为空且尾部为0，删去
		iter = integer.rbegin();	//再次指向尾部
		//整数部分的“尾部”就是最高位，如00515.424900的左两个0
	}

	if (integer.size() == 0 && decimal.size() == 0)	//如果整数、小数全为空
	{
		tag = true;
	}

	if (integer.size() == 0)	//如果整数部分是0
	{
		integer.push_back(0);
	}

	vector<char>::const_iterator it = decimal.begin();	//对小数部分
	while (!decimal.empty() && (*it) == 0)
	{
		it = decimal.erase(it);	//指向不为空且首部为0，删去
		//小数部分的“首部”就是最低位，上例中的右两个0
	}

	if (decimal.size() == 0)	//如果小数部分是0
	{
		decimal.push_back(0);
	}
}

WFloat::WFloat()	//默认构造函数
{
	tag = true;
	integer.push_back(0);
	decimal.push_back(0);
}

WFloat::WFloat(int num)	//用整型初始化
{
	if (num >= 0)	//判断正负
	{
		tag = true;
	}
	else
	{
		tag = false;
		num *= (-1);
	}
	do {
		integer.push_back((char)(num % 10));	//按位倒序写入整数部分
		num /= 10;
	} while (num != 0);

	decimal.push_back(0);	//因为用整数赋值，小数部分为0
}

WFloat::WFloat(string &num)	//用字符串初始化，格式形如"-123.456"、"1.0"
{
	bool type = true;	//用于判断小数部分是否结束
	tag = true;	//默认为正数，读到'-'再变为负数
	for (string::reverse_iterator iter = num.rbegin(); iter < num.rend(); iter++)	  //逆向迭代
	{
		char ch = (*iter);
		if (ch == '.')	//遇到小数点则开始向整数部分写入
		{
			type = false;
			iter++;
		}
		if (iter == num.rend() - 1)	//读取正负号
		{
			if (ch == '+')
			{
				break;
			}
			if (ch == '-')
			{
				tag = false;
				break;
			}
		}
		//利用逆向迭代器，将整个数据倒序存入
		if (type)
			decimal.push_back((char)((*iter) - '0'));
		else
			integer.push_back((char)((*iter) - '0'));
	}
}

WFloat::WFloat(const WFloat &num)	//利用高精度类初始化
{
	integer = num.integer;
	decimal = num.decimal;
	tag = num.tag;
}

WFloat WFloat::operator=(const WFloat& num)	//赋值（拷贝）操作
{
	integer = num.integer;
	decimal = num.decimal;
	tag = num.tag;
	return (*this);
}

WFloat operator-(const WFloat& num)	//取负操作
{
	WFloat temp(num);
	temp.tag = !temp.tag;
	return temp;
}

WFloat WFloat::abs() const	//取绝对值
{
	if (tag)
		return (*this);
	else
		return -(*this);
}

ostream& operator<<(ostream& out, const WFloat& num)	//输出重载
{
	if (!num.tag)	//负数
	{
		out << "-";
	}

	for (vector<char>::const_reverse_iterator iter = num.integer.rbegin(); iter != num.integer.rend(); iter++)  //输出整数部分
	{
		out << (char)((*iter) + '0');
	}

	cout << '.';

	for (vector<char>::const_reverse_iterator iter = num.decimal.rbegin(); iter != num.decimal.rend(); iter++)  //输出小数部分
	{
		out << (char)((*iter) + '0');
	}
	return out;
}

istream& operator>>(istream& in, WFloat& num)	//输入重载
{
	string str;
	in >> str;
	num = WFloat(str);
	return in;
}

WFloat operator+=(WFloat& num1, const WFloat& num2)	//加等于重载
{
	if (num1.tag == num2.tag)	//只处理同符号数，异号由-减法处理
	{
		vector<char>::iterator iter1;
		vector<char>::const_iterator iter2, it;

		//先处理小数部分
		int num1_decimal_size = num1.decimal.size();	//小数部分长度
		int num2_decimal_size = num2.decimal.size();
		char carry = 0;	//进位
		if (num1_decimal_size < num2_decimal_size)	//如果num2小数部分更长
		{
			iter1 = num1.decimal.begin();
			iter2 = num2.decimal.begin();
			iter2 = iter2 - (num1_decimal_size - num2_decimal_size);	//将指向调整到一一对应的位置

			while (iter1 != num1.decimal.end() && iter2 != num2.decimal.end())
			{
				(*iter1) = (*iter1) + (*iter2) + carry;
				carry = ((*iter1) > 9);	//如果大于9则carry=1
				(*iter1) = (*iter1) % 10;
				iter1++;
				iter2++;
			}

			it = num2.decimal.begin();
			iter2 = num2.decimal.end();
			iter2 = iter2 - num1_decimal_size - 1;	//指向长出部分
			while (iter2 != it)
			{
				num1.decimal.insert(num1.decimal.begin(), *iter2);
				iter2--;
			}
			num1.decimal.insert(num1.decimal.begin(), *iter2);
			iter1 = num1.decimal.begin();
		}
		else
			if (num1_decimal_size > num2_decimal_size) //如果num1小数部分更长，同理
			{
				iter1 = num1.decimal.begin();
				iter1 = iter1 + (num1_decimal_size - num2_decimal_size);
				//将指向调整到一一对应的位置
				iter2 = num2.decimal.begin();

				while (iter1 != num1.decimal.end() && iter2 != num2.decimal.end())
				{
					(*iter1) = (*iter1) + (*iter2) + carry;
					carry = ((*iter1) > 9);	//如果大于9则carry=1
					(*iter1) = (*iter1) % 10;
					iter1++;
					iter2++;
				}
			}
			else
			{
				iter1 = num1.decimal.begin();	//如果二者等长
				iter2 = num2.decimal.begin();
				while (iter1 != num1.decimal.end() && iter2 != num2.decimal.end())
				{
					(*iter1) = (*iter1) + (*iter2) + carry;
					carry = ((*iter1) > 9);	//如果大于9则carry=1
					(*iter1) = (*iter1) % 10;
					iter1++;
					iter2++;
				}
			}

		//再处理整数部分
		iter1 = num1.integer.begin();
		iter2 = num2.integer.begin();
		//从个位开始相加
		while (iter1 != num1.integer.end() && iter2 != num2.integer.end())
		{
			(*iter1) = (*iter1) + (*iter2) + carry;
			carry = ((*iter1) > 9);	//如果大于9则carry=1
			(*iter1) = (*iter1) % 10;
			iter1++;
			iter2++;
		}
		//总会有一个先到达end()
		while (iter1 != num1.integer.end())	//如果被加数更长，处理进位
		{
			(*iter1) = (*iter1) + carry;
			carry = ((*iter1) > 9);	//如果大于9则carry=1
			(*iter1) = (*iter1) % 10;
			iter1++;
		}
		while (iter2 != num2.integer.end())	//加数更长
		{
			char val = (*iter2) + carry;
			carry = (val > 9);
			val %= 10;
			num1.integer.push_back(val);
			iter2++;
		}
		if (carry != 0)	//如果还有进位，则说明要添加一位
		{
			num1.integer.push_back(carry);
		}
		num1.trim();
		return num1;
	}
	else
	{	//如果异号
		if (num1.tag)	//如果被加数为正，加数为负，相当于减等于
		{
			WFloat temp(-num2);
			return num1 -= temp;
		}
		else
		{
			WFloat temp(-num1);
			return num1 = num2 - temp;
		}
	}
}

WFloat operator-=(WFloat& num1, const WFloat& num2)	//减等于重载
{
	if (num1.tag == num2.tag)	//只处理同号，异号由+加法处理
	{
		if (num1.tag)	//如果同为正
		{
			if (num1 < num2)	//且被减数小
			{
				WFloat temp(num2 - num1);
				num1 = -temp;
				num1.trim();
				return num1;
			}
		}
		else
		{
			if (-num1 > -num2)	//如果同为负，且被减数绝对值大
				return num1 = -((-num1) - (-num2));
			else
				return num1 = (-num2) - (-num1);
		}

		//下面是同为正，且减数小的情况
		//小数部分 
		char borrow = 0;  //借位
		int num1_decimal_size = num1.decimal.size();
		int num2_decimal_size = num2.decimal.size();
		vector<char>::iterator it1 = num1.decimal.begin();
		vector<char>::const_iterator it2 = num2.decimal.begin();

		if (num1_decimal_size > num2_decimal_size)	//如果被减数小数部分更长
		{
			num1_decimal_size -= num2_decimal_size;	//长出部分
			it1 = it1 + num1_decimal_size;	//跳过长出部分
		}
		else
		{	//如果减数的小数部分更长，则需要给被减数补0
			int number = num2_decimal_size - num1_decimal_size;
			while (number != 0)
			{
				num1.decimal.insert(num1.decimal.begin(), 0); //缺少的位数补0
				number--;
			}
			it1 = num1.decimal.begin();	//插入后需要重新指向
			it2 = num2.decimal.begin();
		}
		while ((it1 != num1.decimal.end()) && (it2 != num2.decimal.end()))
		{
			(*it1) = (*it1) - (*it2) - borrow;
			borrow = 0;
			if ((*it1) < 0)
			{
				borrow = 1;
				(*it1) += 10;
			}
			it1++;
			it2++;
		}
		//整数部分
		vector<char>::iterator iter1;
		vector<char>::const_iterator iter2;
		iter1 = num1.integer.begin();
		iter2 = num2.integer.begin();

		while (iter1 != num1.integer.end() && iter2 != num2.integer.end())
		{
			(*iter1) = (*iter1) - (*iter2) - borrow;
			borrow = 0;
			if ((*iter1) < 0) {
				borrow = 1;
				(*iter1) += 10;
			}
			iter1++;
			iter2++;
		}
		while (iter1 != num1.integer.end()) {
			(*iter1) = (*iter1) - borrow;
			borrow = 0;
			if ((*iter1) < 0)
			{
				borrow = 1;
				(*iter1) += 10;
			}
			else break;
			iter1++;
		}
		num1.trim();	//把多余的0去掉
		return num1;
	}
	else
	{
		//如果异号
		if (num1 > WFloat::ZERO)
		{
			WFloat temp(-num2);
			return num1 += temp;
		}
		else
		{
			WFloat temp(-num1);
			return num1 = -(num2 + temp);
		}
	}
}

WFloat operator*=(WFloat& num1, const WFloat& num2)	//乘等于重载
{
	WFloat result(0);	//储存结果
	if (num1 == WFloat::ZERO || num2 == WFloat::ZERO)	//有0做乘数得0
		result = WFloat::ZERO;
	else
	{
		int size = 0;
		vector<char>temp_num1(num1.integer.begin(), num1.integer.end());	//一个临时变量，用于将整数部分与小数部分合并
		if (num1.decimal.size() != 1 || (num1.decimal.size() == 1 && (*num1.decimal.begin()) != 0)) //如果被乘数有小数部分，插入小数
		{
			temp_num1.insert(temp_num1.begin(), num1.decimal.begin(), num1.decimal.end());
			size += num1.decimal.size();
		}

		vector<char>temp_num2(num2.integer.begin(), num2.integer.end());	//一个临时变量，用于将整数部分与小数部分合并
		if (num2.decimal.size() != 1 || (num2.decimal.size() == 1 && (*num2.decimal.begin()) != 0)) //如果被乘数有小数部分，插入小数
		{
			temp_num2.insert(temp_num2.begin(), num2.decimal.begin(), num2.decimal.end());
			size += num2.decimal.size();
		}

		//开始乘法
		vector<char>::const_iterator iter2 = temp_num2.begin();
		while (iter2 != temp_num2.end())
		{
			if (*iter2 != 0)
			{
				deque<char>temp(temp_num1.begin(), temp_num1.end());
				char carry = 0;	//进位
				deque<char>::iterator iter1 = temp.begin();
				while (iter1 != temp.end())	//被乘数乘以某一位乘数
				{
					(*iter1) *= (*iter2);
					(*iter1) += carry;
					carry = (*iter1) / 10;
					(*iter1) %= 10;
					iter1++;
				}
				if (carry != 0)
				{
					temp.push_back(carry);
				}
				int num_of_zeros = iter2 - temp_num2.begin();	//计算错位
				while (num_of_zeros--)
					temp.push_front(0);	//乘得结果后面添0
				WFloat temp2;
				temp2.integer.clear();
				temp2.integer.insert(temp2.integer.end(), temp.begin(), temp.end());
				temp2.trim();
				result = result + temp2;
			}
			iter2++;
		}
		result.tag = ((num1.tag && num2.tag) || (!num1.tag && !num2.tag));

		//由于我们将小数和整数合并在一起，因此下面要把小数点重新添上
		if (size != 0)
		{
			if (size >= result.integer.size())	//说明需要补前导0
			{
				int n = size - result.integer.size();
				for (int i = 0; i <= n; i++)
					result.integer.insert(result.integer.end(), 0);
			}
			result.decimal.clear();
			result.decimal.insert(result.decimal.begin(), result.integer.begin(), result.integer.begin() + size);
			result.integer.erase(result.integer.begin(), result.integer.begin() + size);
		}
	}
	num1 = result;
	num1.trim();
	return num1;
}

WFloat operator/=(WFloat& num1, const WFloat& num2)	//除等于重载
{
	if (num2 == WFloat::ZERO)
		throw DividedByZeroException();
	if (num1 == WFloat::ZERO)
		return num1;

	WFloat temp_num1 = num1;
	WFloat temp_num2 = num2;
	if (temp_num1.tag == false || temp_num2.tag == false)	//转换成无符号除法来做
	{
		temp_num1.tag = true;
		temp_num2.tag = true;
	}

	int Integer_Size = 0;	//整数部分应为几位
	if ((temp_num2.decimal.size() == 1) && (*(temp_num2.decimal.begin()) == 0)) {} //如果除数没有小数部分，不做操作
	else
	{
		//否则把除数和乘数同时扩大，直到除数为整数（只对Integer部分运算）
		int t = temp_num2.decimal.size();
		while (t--)
		{
			temp_num1 = temp_num1 * WFloat::TEN;
			temp_num2 = temp_num2 * WFloat::TEN;
		}
	}
	if (temp_num1 < temp_num2)	//被除数小于除数，应该是0.xxx
	{
		while (temp_num1 < temp_num2)
		{
			temp_num1 *= WFloat::TEN;
			Integer_Size--;
		}
	}
	else
	{
		while (temp_num1 > temp_num2)
		{
			temp_num1.decimal.push_back(*temp_num1.integer.begin());
			temp_num1.integer.erase(temp_num1.integer.begin());
			Integer_Size++;
		}
	}

	int k = ACCURACY;
	WFloat quotient(0);	//商

	while (k--)
	{
		if (temp_num1 < temp_num2)
		{
			temp_num1 = temp_num1 * WFloat::TEN;
			quotient = quotient * WFloat::TEN;
		}
		else
		{
			int i;
			WFloat compare;
			for (i = 1; i <= 10; i++)	//“试商”
			{
				WFloat BF(i);
				compare = temp_num2 * BF;
				if (compare > temp_num1)
					break;
			}
			compare -= temp_num2;
			temp_num1 -= compare;
			WFloat index(i - 1);
			quotient = quotient + index;
		}
	}

	if (Integer_Size < 0)	//如果是小数除以大数，结果为0.xxx
	{
		vector<char> temp(quotient.integer.begin(), quotient.integer.end());
		quotient.integer.clear();
		quotient.integer.push_back(0);	//整数部分为0

		quotient.decimal.clear();
		int count_zero = -Integer_Size;
		//下面先补充前导0
		while (--count_zero)
		{
			quotient.decimal.insert(quotient.decimal.begin(), 0);
		}
		quotient.decimal.insert(quotient.decimal.begin(), temp.begin(), temp.end());
	}
	else
	{
		if (quotient.integer.size() > Integer_Size)
		{
			vector<char> temp(quotient.integer.begin(), quotient.integer.end());

			quotient.integer.clear();	//这里如果不清空会有错误

			quotient.integer.assign(temp.end() - Integer_Size, temp.end());

			quotient.decimal.clear();	//同理需要清空

			quotient.decimal.insert(quotient.decimal.begin(), temp.begin(), temp.end() - Integer_Size);
		}
		else
		{
			//这一部分意义不明，我觉得不会走到这个分支
			int t = Integer_Size - quotient.integer.size();
			while (t--)
			{
				quotient = quotient * WFloat::TEN;
			}
		}
	}
	quotient.tag = ((num1.tag && num2.tag) || (!num1.tag && !num2.tag));
	num1 = quotient;
	num1.trim();
	return num1;
}

WFloat operator+(const WFloat& num1, const WFloat& num2)	//调用+=
{
	WFloat temp(num1);
	temp += num2;
	return temp;
}

WFloat operator-(const WFloat& num1, const WFloat& num2)	//调用-=
{
	WFloat temp(num1);
	temp -= num2;
	return temp;
}

WFloat operator*(const WFloat& num1, const WFloat& num2)	//调用*=
{
	WFloat temp(num1);
	temp *= num2;
	return temp;
}

WFloat operator/(const WFloat& num1, const WFloat& num2)  throw(DividedByZeroException)	//调用/=
{
	WFloat temp(num1);
	temp /= num2;
	return temp;
}

bool operator<(const WFloat& num1, const WFloat& num2)	//小于重载
{
	bool sign;	//返回值
	if (num1.tag != num2.tag)	//如果异号
	{
		sign = !num1.tag;	//如果num1正，则不小于;反之，则小于
		return sign;
	}
	else
	{
		//如果同号，先比较整数再比较小数
		if (num1.integer.size() != num2.integer.size())	//如果整数部分不等长
		{
			if (num1.tag)	//如果同为正,则整数部分长的大
			{
				sign = num1.integer.size() < num2.integer.size();
				return sign;
			}
			else
			{
				//同为负，则整数部分长的小
				sign = num1.integer.size() > num2.integer.size();
				return sign;
			}
		}
		//如果整数部分等长
		vector<char>::const_reverse_iterator iter1, iter2;
		iter1 = num1.integer.rbegin();
		iter2 = num2.integer.rbegin();
		while (iter1 != num1.integer.rend())
		{
			if (num1.tag && *iter1 < *iter2)
				return true;
			if (num1.tag && *iter1 > *iter2)
				return false;
			if (!num1.tag && *iter1 > *iter2)
				return true;
			if (!num1.tag && *iter1 < *iter2)
				return false;
			iter1++;
			iter2++;
		}

		//下面比较小数部分
		vector<char>::const_reverse_iterator it1, it2;
		it1 = num1.decimal.rbegin();
		it2 = num2.decimal.rbegin();
		while (it1 != num1.decimal.rend() && it2 != num2.decimal.rend())
		{
			if (num1.tag && *it1 < *it2)
				return true;
			if (num1.tag && *it1 > *it2)
				return false;
			if (!num1.tag && *it1 > *it2)
				return true;
			if (!num1.tag && *it1 < *it2)
				return false;
			it1++;
			it2++;
		}
		//如果整数部分，而小数部分停止前全部一样，那么看谁的小数位更多
		return(num1.tag && it2 != num2.decimal.rend()) || (!num1.tag && it1 != num1.decimal.rend());
	}
}

bool operator>(const WFloat& num1, const WFloat& num2)	//大于重载
{
	bool tag = !(num1 <= num2);
	return tag;
}

bool operator==(const WFloat& num1, const WFloat& num2)	//等于重载
{
	if (num1.tag != num2.tag)
		return false;
	if (num1.integer.size() != num2.integer.size())
		return false;
	if (num1.decimal.size() != num2.decimal.size())
		return false;

	//如果长度和符号相同，那么下面逐位比较
	vector<char>::const_iterator iter1, iter2;
	iter1 = num1.decimal.begin();
	iter2 = num2.decimal.begin();
	while (iter1 != num1.decimal.end())
	{
		if (*iter1 != *iter2)
			return false;
		iter1++;
		iter2++;
	}

	iter1 = num1.integer.begin();
	iter2 = num2.integer.begin();
	while (iter1 != num1.integer.end())
	{
		if (*iter1 != *iter2)
			return false;
		iter1++;
		iter2++;
	}
	return true;
}

bool operator!=(const WFloat& num1, const WFloat& num2)
{
	return !(num1 == num2);
}

bool operator>=(const WFloat& num1, const WFloat& num2)
{
	bool tag = (num1 > num2) || (num1 == num2);
	return tag;
}

bool operator<=(const WFloat& num1, const WFloat& num2)
{
	bool tag = (num1 < num2) || (num1 == num2);
	return tag;
}