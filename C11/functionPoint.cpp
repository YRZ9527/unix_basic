#include "iostream"
#include "vector"
using namespace std;

void printItem(const vector<int> &items, int (*func)(const int, const int))
{
    int index = func(items.size(), items[1]);
    if (items[index] > items.size())
        throw "The value is bigger than index";
    cout << "index: " << index << "," << items[index] << endl;
}

int twoSum(const int a, const int b)
{
    return a + b;
}
void (*funcPrint)(const vector<int> &items, int (*func)(const int, const int)) = printItem;
int (*sum)(const int a, const int b) = twoSum;
int main(int argc, char **argv)
{
    std::vector<int> test = {32, 12123, 123, -1212, 11, 33, 232, 1};
    int index = 2;
    
    cout << "please input " << endl;
    funcPrint(test, sum);
    return 0;
}