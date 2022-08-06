#include"iostream"
using namespace std;

void print_float(float value)
{
    cout<<"Float value: "<<value<<endl;
}
void print_int(int value)
{
    cout<<"Int value: "<<value<<endl;
}
template<typename Func>
void call_twice(Func func)
{
    func(1);
    func(0);
}
int main()
{
    auto myfunc = [&](int n)->int
    {
        return n*10;
    };
    call_twice(myfunc);
    // call_twice(print_int);
    // call_twice(print_float);
}