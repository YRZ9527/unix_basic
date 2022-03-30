#include "iostream"
//using namespace std;

template<typename T>
T max(T a, T b) { return a > b ? a : b; }
template<typename T>
T max(T a, T b, T c) {
    return max(max(a, b), c);
}

int max(int a, int b) { 
    std::cout<<2;
    return b < a ? a : b;
}

int main() {
    std::cout<<::max(3,1,2);
}