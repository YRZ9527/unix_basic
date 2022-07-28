// stoi example
#include <iostream> // std::cout
#include <string>   // std::string, std::stoi
#include <vector>   // std::vector
#include <iomanip>
#include <fstream>

using namespace std;

double calculate(string test)
{
    long double tmp;
    long double tmpBig;
    long double tmpSmall;
    tmpBig = stoi(test.substr(1, 5), nullptr, 16) * 7.00000;
    tmpSmall = stol(test.substr(6, 10), nullptr, 16) /1e9 * 1.2 / 64;
    tmp = tmpSmall + tmpBig;

    return tmp;
}

void Channel(vector<string> test, vector<double> &Channel_A, vector<double> &Channel_B, vector<double> &Channel_C, vector<double> &Channel_D)
{
    for (int i = 0; i < test.size(); i++)
    {
        
        string tmp = test[i].substr(0, 1);
        int intTmp = stoi(tmp, nullptr, 16);
        double res = calculate(test[i]);
        if ((intTmp & 2) == 2)
            Channel_A.push_back(res);
        if ((intTmp & 1) == 1)
            Channel_B.push_back(res);
        if ((intTmp & 3) == 3)
            Channel_C.push_back(res);
        if ((intTmp & 0) == 0)
            Channel_D.push_back(res);
    }
}



int main()
{
    ofstream outfile("out.txt", ios::trunc);

    vector<string> test;
    vector<double>A,B,C,D;
    string dec = "1000001E4DB642021000010E524A21F91000010E56DE02011000010E5B71E2001000010E6005C1FD1000010E6499A2001000010E692D82011000010E6DC162031000010E725541FD1000010E76E922011000010E7B7D02021000010E8010E1FF1000010E84A4C1FF1000010E8938A1FF1000010E8DCC81FC1000010E926061FF1000010E96F442001000010E9B8822011000010EA01C02061000010EA4AFE2031000010EA943C1FF1000010EADD7A2001000010EB26B81FA1000010EB6FF61FD1000010EBB9342001000010EC02722001000010EC4BB02011000010EC94EE2001000010ECDE2C1FD1000010ED276A2001000010ED70A81FD1000010EDB9E62001000010EE03242021000010EE4C622001000010EE95A02041000010EEDEDE2031000010EF281C2001000010EF715A2011000010EFBA982011000010F003D62041000010F04D142001000010F096522011000010F0DF902001000010F128CE2021000010F1720C2001000010F1BB4A1FF1000010F204882031000010F24DC62041000010F297041FD1000010F2E0422001000010F329802001000010F372BE2011000010F3BBFC2011000010F4053A2061000010F44E782001000010F497B6201"; //   string hex1 = "403C";
    //   string bin = "-101010";
    string sign1 = "1000010D4DB64202";
    string sign2 = "4DB64202";
    string sign3 = "02100001";
    test.push_back(sign1); 
    test.push_back(sign2);
    test.push_back(sign3);
    Channel(test,A,B,C,D);
    cout<<fixed<<setprecision(13)<<D[1]<<endl;
    for(auto i : D)
    {
        outfile <<"A:"<< fixed << setprecision(13)<<i<<endl;
    }
    outfile.close();
    
    printf("%.12f",D[1]);

return 0;
}
