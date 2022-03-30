#include "iostream"

template <typename T>
class Stack
{
public:
    Stack();
    Stack(const Stack<T> &); // T是同一类型的类模板才能拷贝
    Stack<T> &operator=(const Stack<T> &);
    void push(const T &);
    void pop();
    const T &top() const;
    bool empty() const;

private:
    std::vector<T> v;
};

template <typename T>
Stack<T>::Stack()
{
}

template <typename T>
Stack<T>::Stack(const Stack<T> &rhs) : v(rhs.v)
{
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &rhs)
{
    v = rhs.v;
    return *this;
}

template <typename T>
void Stack<T>::push(const T &x)
{
    v.emplace_back(x);
}

template <typename T>
void Stack<T>::pop()
{
    assert(!v.empty());
    v.pop_back();
}

template <typename T>
const T &Stack<T>::top() const
{
    assert(!v.empty());
    return v.back();
}

template <typename T>
bool Stack<T>::empty() const
{
    return v.empty();
}

int main()
{
  using IntStack = Stack<int>; // typedef Stack<int> IntStack
  IntStack intStack; // Stack<int> intStack
  intStack.push(42);
  std::cout << intStack.top(); // 42
  Stack<std::string> stringStack;
  stringStack.push("hi");
  std::cout << stringStack.top(); // hi
  stringStack.pop();
}