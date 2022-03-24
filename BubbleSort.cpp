#include "head.h"
template <typename T>
bool ascending(T x, T y) { return x > y; }

template <typename T>
bool descending(T x, T y) { return x < y; }

template <typename T>
void bubblesort(T *a, int n, bool (*cmpfunc)(T, T))
{

    bool sorted = false;

    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i < n - 1; i++)
        {
            if (cmpfunc(a[i], a[i + 1]))
            {
                swap(a[i], a[i + 1]);
                sorted = false;
            }
        }
        n--;
    }
}

int main()
{

    int arr[8] = {12, 3, 532, 1221, 4, 66, 2, -32};
    double b[8] = {53.3, 234, 3, 345, 21, 31, -23, -21.2};
    bubblesort<double>(b, 8, ascending);

    for (auto e : b)
        std::cout << e << " ";
    std::cout << std::endl;

    bubblesort<int>(arr, 8, ascending);

    for (auto e : arr)
        std::cout << e << " ";
    std::cout << std::endl;

    return 0;
}