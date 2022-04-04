#define STACK_INIT_SIZE 100 ///the size of stack after initialized
#define STACK_INCREMENT 10  ///the increment of stack growth
class Stack{
private:
    int *base;///using array to store element
    int top;///use index(index of base) to find the top element of stack
    int stacksize;
    ///will be called when push a element to a full stack(top = stacksize)
    bool ReallocateMemory();
public:
    ///apply for memory and form a empty stack
    Stack();
    ///destroy the stack s and s won't exist anymore
    void DestroyStack();
    ///clear the stack s and s become a empty stack
    void ClearStack();
    ///get top element of stack while s is not empty otherwise return false
    bool GetTop(int &e);
    ///insert a element to the stack
    bool Push(int e);
    ///remove the top element and return it
    bool Pop(int &e);
    ///get stack size
    int GetSize();
};