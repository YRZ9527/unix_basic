#include "iostream"
#include "thread"
#include "chrono"
using namespace std;

void func(int num, string str)
{
    for (auto i = 0; i < 10; ++i)
    {
        cout << "子线程: i = " << i << "num: "
             << num << ", str: " << str << endl;
    }
}
void func1()
{
    for (int i = 0; i < 10; ++i)
    {
        cout << "子线程: i = " << i << endl;
    }
}

int main(int argc, char *argv[])
{
    cout << "main thread id =" << this_thread::get_id() << endl;
    thread t(func, 520, "i love you ");
    thread t1(func1);

    // thread t1(func);
    cout << "t thread id" << t.get_id() << endl;
    cout << "t1 thread id" << t1.get_id() << endl;
    t.join();
    t1.join();
    int num = thread::hardware_concurrency();
    cout << "CPU number: " << num << endl;
    return 0;
}