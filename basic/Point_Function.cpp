#include "head.h"


int add (int x, int y)
{
    return (x + y);
}

int sub(int x, int y)
{
    return (x - y);
}

void func(int a, int b, int(*f)(int, int))
{
    cout<<"test:"<<f(a,b)<<endl;
}

template<typename T> 
void bubblesort(T *a, int n)
{
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 0; i < n - 1; i++){
            if(a[i] > a[i + 1])
            {
                swap(a[i],a[i + 1]);
                sorted = false;
            }
            n--;
        }
    }
}

template<typename Te>
void display(Te *a){

    for(auto e:a)
    cout<<e<<""<<endl;
}

int main() {


    int arr[8] = {12,3,532,1221,4,66,2,-32};
    double b[8] = {53.3,234,3,345,21,31,-23,-21.2};


    bubblesort<int>(arr,8);
    for(auto e:arr){
        cout<<e<<""<<endl;
    }
    
    func(2,3,add);
    func(4,5,sub);






    return 0;
}