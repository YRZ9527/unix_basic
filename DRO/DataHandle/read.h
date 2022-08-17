#ifndef __READ___
#define __READ___
#include "string"
#include "iostream"
#include "vector"
#include "fstream"

// #include <fstream>
#include <sstream>
using namespace std;
class Read
{
public:
    Read(){cout<<"constructor"<<endl;}
    vector<string> readData(string filePath, string &resTmp);
    ~Read(){};
    void Resplace(string &resTmp);
    

    void findKey(string key, vector<string> tmp,vector<string> &strResult,vector<string>& vectorResult,string &writeStr);
    double calculate(string test);
    void Channel(vector<string> test, vector<double> &Channel_A, vector<double> &Channel_B, vector<double> &Channel_C, vector<double> &Channel_D);

    
private:
    string filePath;
    // vector<string> resTmp;
};

#endif