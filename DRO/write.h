#include "read.h"

string stuff = "aa";
string head = "352ef853";
string tail = "5a5a5a5a";
class Write
{
public:
    Write(string outPathName) : outPathName(outPathName)
    {
        ofstream outFile_A(outPathName, ios::out | ios::binary);
    }
    void writeFile(const string filename, vector<string> &wrietTmp);
    void display();

    ~Write(){
        // outFile.close();

    };

private:
    string outPathName;
};