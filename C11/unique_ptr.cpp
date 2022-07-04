//智能指针的jiandanshiyong
#include "iostream"
#include "memory"
#include "mutex"
using namespace std;
class Test {
    public:
        Test()
        {
            cout<<"Create"<<endl;
        }
        ~Test()
        {
            cout<<"析构函数"<<endl;
        }
        
};

int main(int argc, char** argv) {
    unique_ptr<int> up1(new int(11)); // create a small pointer object
    cout<<*up1<<endl;

    unique_ptr<Test> test(new Test());
    
    //unique_ptr<Test> test1 = test;
    //不允许使用拷贝构造函数
    // unique_ptr<int> test2 = std::move(up1);
    // //转移
    // cout<<*test2<<endl;
    // cout<<*up1<<endl;
    up1.reset(new int(22));
    cout<<"*up"<<*up1<<endl;

    //释放控制权、但是不释放堆区内存
    int *p = up1.release();
    // cout<<"*up"<<*up1<<endl;
    cout<<*p<<endl;
    delete p;


    return 0;
}