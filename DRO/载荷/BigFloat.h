#pragma once
#include<iostream>
#include<vector>
#include<deque>
#include<string>
#include<algorithm>
using namespace std;

#define ACCURACY 100;	//�����������

class DividedByZeroException {	//����������
public:
	void error()
	{
		cout << "Divided By Zero Exception!" << endl;
	}
};

class WFloat	//�߾��ȸ�������
{
	//�������������
	friend WFloat operator+(const WFloat&, const WFloat&);	//�ӷ�����
	friend WFloat operator-(const WFloat&, const WFloat&);	//��������
	friend WFloat operator*(const WFloat&, const WFloat&);	//�˷�����
	friend WFloat operator/(const WFloat&, const WFloat&) throw(DividedByZeroException);	//��������
	friend WFloat operator-(const WFloat&);	//��������

	//�Ƚ�����
	friend bool operator==(const WFloat&, const WFloat&);	//��������
	friend bool operator!=(const WFloat&, const WFloat&);	//����������
	friend bool operator<(const WFloat&, const WFloat&);	//С������
	friend bool operator<=(const WFloat&, const WFloat&);	//С�ڵ�������
	friend bool operator>(const WFloat&, const WFloat&);	//��������
	friend bool operator>=(const WFloat&, const WFloat&);	//���ڵ�������

	//��չ���������
	friend WFloat operator+=(WFloat&, const WFloat&);	//�ӵ�����
	friend WFloat operator-=(WFloat&, const WFloat&);	//��������
	friend WFloat operator*=(WFloat&, const WFloat&);	//�˵�����
	friend WFloat operator/=(WFloat&, const WFloat&);	//��������

	//�����������
	friend ostream& operator<<(ostream&, const WFloat&);	//�������
	friend istream& operator>>(istream&, WFloat&);	//��������

public:
	WFloat();
	WFloat(int);	//��һ����������
	WFloat(string&);	//��һ���ַ�������
	WFloat(const WFloat&);	//��һ���߾���������
	WFloat operator=(const WFloat&);	//��ֵ����
	WFloat abs() const;	//ȡ����ֵ
	~WFloat() {}

	static const WFloat ZERO;	//����0
	static const WFloat ONE;	//����1
	static const WFloat TEN;	//����10�����ڳ���������

private:
	vector<char>integer;	//��������
	vector<char>decimal;	//С������
	void trim();	//���������ɾȥ
	bool tag;	//������ʾ������trueΪ��
};

const WFloat WFloat::ZERO = WFloat(0);
const WFloat WFloat::ONE = WFloat(1);
const WFloat WFloat::TEN = WFloat(10);

void WFloat::trim()
{
	//��Ϊ����������洢�ģ�����������β����С�����ײ����ܻ��ж����0
	vector<char>::reverse_iterator iter = integer.rbegin();	//����������
	while (!integer.empty() && (*iter) == 0)
	{
		integer.pop_back();	//ָ��Ϊ����β��Ϊ0��ɾȥ
		iter = integer.rbegin();	//�ٴ�ָ��β��
		//�������ֵġ�β�����������λ����00515.424900��������0
	}

	if (integer.size() == 0 && decimal.size() == 0)	//���������С��ȫΪ��
	{
		tag = true;
	}

	if (integer.size() == 0)	//�������������0
	{
		integer.push_back(0);
	}

	vector<char>::const_iterator it = decimal.begin();	//��С������
	while (!decimal.empty() && (*it) == 0)
	{
		it = decimal.erase(it);	//ָ��Ϊ�����ײ�Ϊ0��ɾȥ
		//С�����ֵġ��ײ����������λ�������е�������0
	}

	if (decimal.size() == 0)	//���С��������0
	{
		decimal.push_back(0);
	}
}

WFloat::WFloat()	//Ĭ�Ϲ��캯��
{
	tag = true;
	integer.push_back(0);
	decimal.push_back(0);
}

WFloat::WFloat(int num)	//�����ͳ�ʼ��
{
	if (num >= 0)	//�ж�����
	{
		tag = true;
	}
	else
	{
		tag = false;
		num *= (-1);
	}
	do {
		integer.push_back((char)(num % 10));	//��λ����д����������
		num /= 10;
	} while (num != 0);

	decimal.push_back(0);	//��Ϊ��������ֵ��С������Ϊ0
}

WFloat::WFloat(string &num)	//���ַ�����ʼ������ʽ����"-123.456"��"1.0"
{
	bool type = true;	//�����ж�С�������Ƿ����
	tag = true;	//Ĭ��Ϊ����������'-'�ٱ�Ϊ����
	for (string::reverse_iterator iter = num.rbegin(); iter < num.rend(); iter++)	  //�������
	{
		char ch = (*iter);
		if (ch == '.')	//����С������ʼ����������д��
		{
			type = false;
			iter++;
		}
		if (iter == num.rend() - 1)	//��ȡ������
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
		//������������������������ݵ������
		if (type)
			decimal.push_back((char)((*iter) - '0'));
		else
			integer.push_back((char)((*iter) - '0'));
	}
}

WFloat::WFloat(const WFloat &num)	//���ø߾������ʼ��
{
	integer = num.integer;
	decimal = num.decimal;
	tag = num.tag;
}

WFloat WFloat::operator=(const WFloat& num)	//��ֵ������������
{
	integer = num.integer;
	decimal = num.decimal;
	tag = num.tag;
	return (*this);
}

WFloat operator-(const WFloat& num)	//ȡ������
{
	WFloat temp(num);
	temp.tag = !temp.tag;
	return temp;
}

WFloat WFloat::abs() const	//ȡ����ֵ
{
	if (tag)
		return (*this);
	else
		return -(*this);
}

ostream& operator<<(ostream& out, const WFloat& num)	//�������
{
	if (!num.tag)	//����
	{
		out << "-";
	}

	for (vector<char>::const_reverse_iterator iter = num.integer.rbegin(); iter != num.integer.rend(); iter++)  //�����������
	{
		out << (char)((*iter) + '0');
	}

	cout << '.';

	for (vector<char>::const_reverse_iterator iter = num.decimal.rbegin(); iter != num.decimal.rend(); iter++)  //���С������
	{
		out << (char)((*iter) + '0');
	}
	return out;
}

istream& operator>>(istream& in, WFloat& num)	//��������
{
	string str;
	in >> str;
	num = WFloat(str);
	return in;
}

WFloat operator+=(WFloat& num1, const WFloat& num2)	//�ӵ�������
{
	if (num1.tag == num2.tag)	//ֻ����ͬ�������������-��������
	{
		vector<char>::iterator iter1;
		vector<char>::const_iterator iter2, it;

		//�ȴ���С������
		int num1_decimal_size = num1.decimal.size();	//С�����ֳ���
		int num2_decimal_size = num2.decimal.size();
		char carry = 0;	//��λ
		if (num1_decimal_size < num2_decimal_size)	//���num2С�����ָ���
		{
			iter1 = num1.decimal.begin();
			iter2 = num2.decimal.begin();
			iter2 = iter2 - (num1_decimal_size - num2_decimal_size);	//��ָ�������һһ��Ӧ��λ��

			while (iter1 != num1.decimal.end() && iter2 != num2.decimal.end())
			{
				(*iter1) = (*iter1) + (*iter2) + carry;
				carry = ((*iter1) > 9);	//�������9��carry=1
				(*iter1) = (*iter1) % 10;
				iter1++;
				iter2++;
			}

			it = num2.decimal.begin();
			iter2 = num2.decimal.end();
			iter2 = iter2 - num1_decimal_size - 1;	//ָ�򳤳�����
			while (iter2 != it)
			{
				num1.decimal.insert(num1.decimal.begin(), *iter2);
				iter2--;
			}
			num1.decimal.insert(num1.decimal.begin(), *iter2);
			iter1 = num1.decimal.begin();
		}
		else
			if (num1_decimal_size > num2_decimal_size) //���num1С�����ָ�����ͬ��
			{
				iter1 = num1.decimal.begin();
				iter1 = iter1 + (num1_decimal_size - num2_decimal_size);
				//��ָ�������һһ��Ӧ��λ��
				iter2 = num2.decimal.begin();

				while (iter1 != num1.decimal.end() && iter2 != num2.decimal.end())
				{
					(*iter1) = (*iter1) + (*iter2) + carry;
					carry = ((*iter1) > 9);	//�������9��carry=1
					(*iter1) = (*iter1) % 10;
					iter1++;
					iter2++;
				}
			}
			else
			{
				iter1 = num1.decimal.begin();	//������ߵȳ�
				iter2 = num2.decimal.begin();
				while (iter1 != num1.decimal.end() && iter2 != num2.decimal.end())
				{
					(*iter1) = (*iter1) + (*iter2) + carry;
					carry = ((*iter1) > 9);	//�������9��carry=1
					(*iter1) = (*iter1) % 10;
					iter1++;
					iter2++;
				}
			}

		//�ٴ�����������
		iter1 = num1.integer.begin();
		iter2 = num2.integer.begin();
		//�Ӹ�λ��ʼ���
		while (iter1 != num1.integer.end() && iter2 != num2.integer.end())
		{
			(*iter1) = (*iter1) + (*iter2) + carry;
			carry = ((*iter1) > 9);	//�������9��carry=1
			(*iter1) = (*iter1) % 10;
			iter1++;
			iter2++;
		}
		//�ܻ���һ���ȵ���end()
		while (iter1 != num1.integer.end())	//��������������������λ
		{
			(*iter1) = (*iter1) + carry;
			carry = ((*iter1) > 9);	//�������9��carry=1
			(*iter1) = (*iter1) % 10;
			iter1++;
		}
		while (iter2 != num2.integer.end())	//��������
		{
			char val = (*iter2) + carry;
			carry = (val > 9);
			val %= 10;
			num1.integer.push_back(val);
			iter2++;
		}
		if (carry != 0)	//������н�λ����˵��Ҫ���һλ
		{
			num1.integer.push_back(carry);
		}
		num1.trim();
		return num1;
	}
	else
	{	//������
		if (num1.tag)	//���������Ϊ��������Ϊ�����൱�ڼ�����
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

WFloat operator-=(WFloat& num1, const WFloat& num2)	//����������
{
	if (num1.tag == num2.tag)	//ֻ����ͬ�ţ������+�ӷ�����
	{
		if (num1.tag)	//���ͬΪ��
		{
			if (num1 < num2)	//�ұ�����С
			{
				WFloat temp(num2 - num1);
				num1 = -temp;
				num1.trim();
				return num1;
			}
		}
		else
		{
			if (-num1 > -num2)	//���ͬΪ�����ұ���������ֵ��
				return num1 = -((-num1) - (-num2));
			else
				return num1 = (-num2) - (-num1);
		}

		//������ͬΪ�����Ҽ���С�����
		//С������ 
		char borrow = 0;  //��λ
		int num1_decimal_size = num1.decimal.size();
		int num2_decimal_size = num2.decimal.size();
		vector<char>::iterator it1 = num1.decimal.begin();
		vector<char>::const_iterator it2 = num2.decimal.begin();

		if (num1_decimal_size > num2_decimal_size)	//���������С�����ָ���
		{
			num1_decimal_size -= num2_decimal_size;	//��������
			it1 = it1 + num1_decimal_size;	//������������
		}
		else
		{	//���������С�����ָ���������Ҫ����������0
			int number = num2_decimal_size - num1_decimal_size;
			while (number != 0)
			{
				num1.decimal.insert(num1.decimal.begin(), 0); //ȱ�ٵ�λ����0
				number--;
			}
			it1 = num1.decimal.begin();	//�������Ҫ����ָ��
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
		//��������
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
		num1.trim();	//�Ѷ����0ȥ��
		return num1;
	}
	else
	{
		//������
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

WFloat operator*=(WFloat& num1, const WFloat& num2)	//�˵�������
{
	WFloat result(0);	//������
	if (num1 == WFloat::ZERO || num2 == WFloat::ZERO)	//��0��������0
		result = WFloat::ZERO;
	else
	{
		int size = 0;
		vector<char>temp_num1(num1.integer.begin(), num1.integer.end());	//һ����ʱ���������ڽ�����������С�����ֺϲ�
		if (num1.decimal.size() != 1 || (num1.decimal.size() == 1 && (*num1.decimal.begin()) != 0)) //�����������С�����֣�����С��
		{
			temp_num1.insert(temp_num1.begin(), num1.decimal.begin(), num1.decimal.end());
			size += num1.decimal.size();
		}

		vector<char>temp_num2(num2.integer.begin(), num2.integer.end());	//һ����ʱ���������ڽ�����������С�����ֺϲ�
		if (num2.decimal.size() != 1 || (num2.decimal.size() == 1 && (*num2.decimal.begin()) != 0)) //�����������С�����֣�����С��
		{
			temp_num2.insert(temp_num2.begin(), num2.decimal.begin(), num2.decimal.end());
			size += num2.decimal.size();
		}

		//��ʼ�˷�
		vector<char>::const_iterator iter2 = temp_num2.begin();
		while (iter2 != temp_num2.end())
		{
			if (*iter2 != 0)
			{
				deque<char>temp(temp_num1.begin(), temp_num1.end());
				char carry = 0;	//��λ
				deque<char>::iterator iter1 = temp.begin();
				while (iter1 != temp.end())	//����������ĳһλ����
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
				int num_of_zeros = iter2 - temp_num2.begin();	//�����λ
				while (num_of_zeros--)
					temp.push_front(0);	//�˵ý��������0
				WFloat temp2;
				temp2.integer.clear();
				temp2.integer.insert(temp2.integer.end(), temp.begin(), temp.end());
				temp2.trim();
				result = result + temp2;
			}
			iter2++;
		}
		result.tag = ((num1.tag && num2.tag) || (!num1.tag && !num2.tag));

		//�������ǽ�С���������ϲ���һ���������Ҫ��С������������
		if (size != 0)
		{
			if (size >= result.integer.size())	//˵����Ҫ��ǰ��0
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

WFloat operator/=(WFloat& num1, const WFloat& num2)	//����������
{
	if (num2 == WFloat::ZERO)
		throw DividedByZeroException();
	if (num1 == WFloat::ZERO)
		return num1;

	WFloat temp_num1 = num1;
	WFloat temp_num2 = num2;
	if (temp_num1.tag == false || temp_num2.tag == false)	//ת�����޷��ų�������
	{
		temp_num1.tag = true;
		temp_num2.tag = true;
	}

	int Integer_Size = 0;	//��������ӦΪ��λ
	if ((temp_num2.decimal.size() == 1) && (*(temp_num2.decimal.begin()) == 0)) {} //�������û��С�����֣���������
	else
	{
		//����ѳ����ͳ���ͬʱ����ֱ������Ϊ������ֻ��Integer�������㣩
		int t = temp_num2.decimal.size();
		while (t--)
		{
			temp_num1 = temp_num1 * WFloat::TEN;
			temp_num2 = temp_num2 * WFloat::TEN;
		}
	}
	if (temp_num1 < temp_num2)	//������С�ڳ�����Ӧ����0.xxx
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
	WFloat quotient(0);	//��

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
			for (i = 1; i <= 10; i++)	//�����̡�
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

	if (Integer_Size < 0)	//�����С�����Դ��������Ϊ0.xxx
	{
		vector<char> temp(quotient.integer.begin(), quotient.integer.end());
		quotient.integer.clear();
		quotient.integer.push_back(0);	//��������Ϊ0

		quotient.decimal.clear();
		int count_zero = -Integer_Size;
		//�����Ȳ���ǰ��0
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

			quotient.integer.clear();	//�����������ջ��д���

			quotient.integer.assign(temp.end() - Integer_Size, temp.end());

			quotient.decimal.clear();	//ͬ����Ҫ���

			quotient.decimal.insert(quotient.decimal.begin(), temp.begin(), temp.end() - Integer_Size);
		}
		else
		{
			//��һ�������岻�����Ҿ��ò����ߵ������֧
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

WFloat operator+(const WFloat& num1, const WFloat& num2)	//����+=
{
	WFloat temp(num1);
	temp += num2;
	return temp;
}

WFloat operator-(const WFloat& num1, const WFloat& num2)	//����-=
{
	WFloat temp(num1);
	temp -= num2;
	return temp;
}

WFloat operator*(const WFloat& num1, const WFloat& num2)	//����*=
{
	WFloat temp(num1);
	temp *= num2;
	return temp;
}

WFloat operator/(const WFloat& num1, const WFloat& num2)  throw(DividedByZeroException)	//����/=
{
	WFloat temp(num1);
	temp /= num2;
	return temp;
}

bool operator<(const WFloat& num1, const WFloat& num2)	//С������
{
	bool sign;	//����ֵ
	if (num1.tag != num2.tag)	//������
	{
		sign = !num1.tag;	//���num1������С��;��֮����С��
		return sign;
	}
	else
	{
		//���ͬ�ţ��ȱȽ������ٱȽ�С��
		if (num1.integer.size() != num2.integer.size())	//����������ֲ��ȳ�
		{
			if (num1.tag)	//���ͬΪ��,���������ֳ��Ĵ�
			{
				sign = num1.integer.size() < num2.integer.size();
				return sign;
			}
			else
			{
				//ͬΪ�������������ֳ���С
				sign = num1.integer.size() > num2.integer.size();
				return sign;
			}
		}
		//����������ֵȳ�
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

		//����Ƚ�С������
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
		//����������֣���С������ֹͣǰȫ��һ������ô��˭��С��λ����
		return(num1.tag && it2 != num2.decimal.rend()) || (!num1.tag && it1 != num1.decimal.rend());
	}
}

bool operator>(const WFloat& num1, const WFloat& num2)	//��������
{
	bool tag = !(num1 <= num2);
	return tag;
}

bool operator==(const WFloat& num1, const WFloat& num2)	//��������
{
	if (num1.tag != num2.tag)
		return false;
	if (num1.integer.size() != num2.integer.size())
		return false;
	if (num1.decimal.size() != num2.decimal.size())
		return false;

	//������Ⱥͷ�����ͬ����ô������λ�Ƚ�
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