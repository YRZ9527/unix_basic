#include "iostream"
#include "vector"
using namespace std;

int main(int argc, char **argv)
{
    vector<int> a = {1,11,12,13,14,15,16,17,18};
    for(auto i : a)
    {
        cout<<i<<endl;
    }
    return 0;
}