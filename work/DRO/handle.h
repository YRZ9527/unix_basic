#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <set>
#include <string>
using namespace std;

class Init
{
    friend class File;
public:
    int getSize();
    Init(char *path) : path(path){};

private:
    char *path;
};

class File 
{
public:
    File(vector<vector<int> >&temp,char *path,int size);
    void hoursResult(vector<vector<int> >temp,vector<int>&monthRes,int size);
    void nonRepeatResult(vector<vector<int> >data,vector<int>& nonRepeatResult,int size);
    

};






