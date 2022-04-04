#include "Stack.h"
///apply for memory and form a empty stack
Stack::Stack(){
    base = new int[STACK_INIT_SIZE];
    top = 0;
    stacksize = STACK_INIT_SIZE;
}
///will be called when push a element to a full stack(top = stacksize)
bool Stack::ReallocateMemory(){
    int * tmp = new int[stacksize+STACK_INCREMENT];
    for(int i = 0; i < top; ++i){
        tmp[i] = base[i];
    }
    delete [] base;
    base = tmp;
    stacksize +=STACK_INCREMENT;
    if(base!=nullptr)
        return true;
    return false;
}
///destroy the stack s and s won't exist anymore
void Stack::DestroyStack()
{
    delete [] base;
    base = nullptr;
    top = 0;
    stacksize = 0;
}
///clear the stack s and s become a empty stack
inline void Stack::ClearStack(){
    top = 0;
}
///get top element of stack while s is not empty otherwise return false
bool Stack::GetTop(int &e){
    if(top==0)
        return false;
    e=base[top-1];
    return true;
}
///insert a element to the stack
bool Stack::Push(int e){
    bool flag;
    if(top==stacksize)
        flag = ReallocateMemory();
    base[top++]=e;
    return flag;
}
///remove the top element and return it
bool Stack::Pop(int &e){
    if(top==0)
        return false;
    e = base[--top];
    return true;
}
///get stack size
inline int Stack::GetSize(){
    return top;
}

