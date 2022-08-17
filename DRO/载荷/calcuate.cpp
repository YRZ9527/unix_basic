#include "iostream"
// #include"mutex"
#include "memory"
#include "vector"
using namespace std;

void calculateRms(vector<long double> tmp)
{
    double sum = std::accumulate(std::begin(tmp), std::end(tmp), 0.0);
    double mean = sum / resultSet.size(); //均值

    double accum = 0.0;
    std::for_each(std::begin(resultSet), std::end(resultSet), [&](const double d)
                  { accum += (d - mean) * (d - mean); });

    double stdev = sqrt(accum / (resultSet.size() - 1)); //方差
}
int main(int argc, char **argv)
{
    return 0;
}