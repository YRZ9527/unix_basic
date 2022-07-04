#include "iostream"
#include "memory"
using namespace std;

int main() {
    shared_ptr<int> sp1 (new int(11));
    shared_ptr<int> sp2 = sp1;
    //拷贝构造
    cout<<sp2.use_count()<<endl;
    //打印计数器
    sp1.reset();
    //释放sp1 只是计数器减1 堆区空间没有释放
    cout<<*sp2<<endl;
    sp2.reset();
    cout<<sp2.use_count()<<endl;
    return 0;
}