#include <iostream>
using namespace std;
#include "Stack.h"

int main()
{
    Stack s;
    int e;
    for(int i = 0;i<110;++i)
        s.Push(i);
    for(int i = 0;i<110;++i)
    {
        if(s.Pop(e))
            cout<<e<<' ';
    }
    cout<<endl;
    return 0;
}