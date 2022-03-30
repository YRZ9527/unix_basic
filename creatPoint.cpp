#include"iostream"
using namespace std;


struct inflatable
{
    char name[20];
    float volume;
    double price;
};
int main() 
{

    int* pointTest = new int(8);
    int *Point;
    Point = pointTest;
    cout<<"result="<<*pointTest<<endl;
    cout<<"result="<<Point<<endl;
    // int night = 1001;
    // int* pt = new int;
    // *pt = 1001;

    // cout<<"night = "<<night<<endl;
    // cout<<"night location = "<<&night<<endl;

    // cout<<"point value = "<<*pt<<endl;
    // cout<<"point location ="<<pt<<endl;


    // double* pd = new double[8];
    // for(int i=1; i<8; i++)
    // {
    //     *(pd) =(double)i; 
    //     cout<<"point pd = "<<*pd<<endl;
    // }
    // delete[] pd;
    // delete pt;

    // double* ptr = new double[3];
    // ptr[0] = 0.21;
    // ptr[1] = 0.1312;
    // ptr[2] = rand();
    // cout<<"point ptr = "<<*(ptr+2)<<endl;

    // inflatable* ps = new inflatable;
    // cout<<"enter name of inflatable"<<endl;
    // cin.get(ps->name,20);

    // cout<<"enter volume"<<endl;
    // cin>>(*ps).volume;
    // cout<<"enter price"<<endl;
    // cin>>(*ps).price;


    // cout<<"result_len"<<ps->name<<endl<<(*ps).volume<<endl<<ps->price<<endl;
    // delete ps;
    return 0;

}