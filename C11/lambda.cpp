#include "iostream"
#include "vector"
using namespace std; //

int maxItem(const vector<int> &temp, int (*func)(int, int))
{

    int max = temp[0];
    for (int item : temp)
    {
        max = func(max, item);
    }
    return max;
}

int main()
{

    vector<int> myV = {32, 14, 24, 2132, 11, 48, 92};
    auto comparexy = [](int x, int y)
    {if (x > y) return x; else return y; };

    cout << "maxItem:" << maxItem(myV, comparexy) << endl;

    return 0;
}