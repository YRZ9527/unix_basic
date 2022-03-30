#include "iostream"
#include "string"
//使用作用域运算符（::）表示指定使用全局命名空间中的 max 模板，
//而非 [std::max]
template<typename T>
T max(const T& a, const T& b) {
     return b < a ? a : b;
     }

int main() {
    std::cout<<::max(1, 4);
    std::cout<<::max(1.0, 3.14);
    std::string s1 = "mathmatics";
    std::string s2 = "math";
    
    std::cout<<::max(s1, s2);
}