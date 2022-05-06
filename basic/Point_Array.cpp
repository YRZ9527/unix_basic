#include <iostream>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
// prototype   实质上三个函数的参数列表是等价的 
const double* f1(const double arr[], int n);
const double* f2(const double [], int);
const double* f3(const double* , int);
 
 
int main(int argc, char *argv[])
{
	double a[3] = {12.1, 3.4, 4.5};
	
	// 声明指针
	const double* (*p1)(const double*, int) = f1;
	cout << "Pointer 1 : " << p1(a, 3) << " : " << *(p1(a, 3)) << endl;
	cout << "Pointer 1 : " << (*p1)(a, 3) << " : " << *((*p1)(a, 3)) << endl;
	
	const double* (*parray[3])(const double *, int) = {f1, f2, f3};   // 声明一个指针数组，存储三个函数的地址 
	cout << "Pointer array : " << parray[2](a, 3) << " : " << *(parray[2](a, 3)) << endl;
	cout << "Pointer array : " << parray[2](a, 3) << " : " << *(parray[2](a, 3)) << endl;
    cout << "Pointer array : " << (*parray[2])(a, 3) << " : " << *((*parray[2])(a, 3)) << endl;
    
	return 0;
}
 
 
const double* f1(const double arr[], int n)
{
	return arr;     // 首地址 
} 
 
const double* f2(const double arr[], int n)
{
	return arr+1;
}
 
const double* f3(const double* arr, int n)
{
	return arr+2;
}
 

