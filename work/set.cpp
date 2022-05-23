#include"iostream"
#include<set>
using namespace std;


int main() {

    set<string> hello;
    string a = "hello";
    string b = "hello";
    string c = "hello1";
    hello.insert(a);
    hello.insert(b);
    hello.insert(c);
    cout<<hello.size()<<"\n";

    return 0;
}