#include "iostream"

template<typename T, typename U>

T max (T a, U b) {
    return a > b ? a : b;
}

template<typename RT, typename T, typename U>
RT max(T a, U b){
    return a > b ? a : b;
    //显示指定
    ::max<int, double, double>(1,3.14);
}
int main() {
    auto m = ::max(1,3.14);
    std::cout<<"m = "<<m<<std::endl;
    return 0;



}