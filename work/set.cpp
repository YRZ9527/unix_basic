#include"iostream"
#include<set>
#include<cmath>
using namespace std;


int main() {
    double a = -2830744.471/1000;
    double b = 4676580.282/1000;
    double c = 3275072.816/1000;
    double res1 = (-138000000000/1000-a);
    double res2 = (-25801311486/1000-b);
    double res3 = (-58050465696/1000-c);
    auto ans = sqrt(res1*res1 + res2*res2 + res3*res3);
    cout<<ans<<endl;
    return 0;
}