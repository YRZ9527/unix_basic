#include"iostream"
using namespace std; //
int main() {
    int a = 1;
    int &b  =  a;
    cout<<decltype(a)<<endl;
    return 0;
}