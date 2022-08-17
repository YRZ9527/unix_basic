#include"iostream"
// #include"mutex"
#include "memory"
#include "vector"
#include "cmath"
using namespace std;

// void calculateRms(vector<long double> tmp)
// {
//     double sum = std::accumulate(std::begin(tmp), std::end(tmp), 0.0);
//     double mean = sum / resultSet.size(); //均值

//     double accum = 0.0;
//     std::for_each(std::begin(resultSet), std::end(resultSet), [&](const double d)
//                   { accum += (d - mean) * (d - mean); });

//     double stdev = sqrt(accum / (resultSet.size() - 1)); //方差
// }

//计算均值
double calAvg(std::vector<double> disValues)
{
    double sum = 0;
    for(int i = 0; i < disValues.size(); i++)
    {
        sum += disValues[i];
    }
    return sum / disValues.size();
}


//计算方差
double calVar(vector<double> disValues)
{
    double avg = calAvg(disValues);
    double sum = 0;
    for(int i = 0; i < disValues.size(); i++)
        sum += pow(disValues[i] - avg, 2);
    return sum / disValues.size();
}

//计算标准差
double calStd(std::vector<double> distValues)
{
    double var = calVar(distValues);
    double sigma = sqrt(var);
    return sigma;
}

//3sigma剔除杂点
vector<double> ThreeSigmaFunction(vector<double>tmp, vector<double>& filterRes, int n)
{
    double avg = calVar(tmp);
    double std = calVar(tmp);
    double SigmaHi = avg - n * std;
    double SigmaLo = std - n * std;

    for(int i = 0; i < filterRes.size(); i++)
    {
        if(tmp[i] > SigmaLo && tmp[i] < SigmaHi)
            filterRes.push_back(tmp[i]);
    }
    return filterRes;
}

//归一化操作
vector<double> min_max_normal(vector<double> tmp)
{
    double avg = calVar(tmp);
    vector<double> m_normal;
    for(int i = 0; i < tmp.size(); i++)
    {
        double max = *max_element(tmp.begin(), tmp.end());
        double min = *min_element(tmp.begin(), tmp.end());

        m_normal.push_back((tmp[i] - min) / (max - min));
    }
}

void filter(vector<double>& filterRes, int time, int n)
{
    for(int i = 0; i < time; i++)
    {
        //  ThreeSigmaFunction()
    }

}


int main(int argc, char **argv)
{
    return 0;
}