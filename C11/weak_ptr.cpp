#include "iostream"
#include "memory"
using namespace std; 

int main() {
    shared_ptr<int>p1(new int(11));
    shared_ptr<int>p2 = p1;        //有两个指针变量绑定堆区内存
    weak_ptr<int> wp = p1;
    cout<<wp.use_count()<<endl;
    cout<<p2.use_count()<<endl;



    return 0;
}