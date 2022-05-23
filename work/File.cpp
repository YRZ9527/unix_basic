#include "File.h"

int main()
{
    ofstream outfile("out.txt", ios::trunc);
    char *path = "1.1.txt";
    
    Size getsize;

    int size = getsize.getSize(path);
    //cout<<size<<endl;
    File test(path,size);
    vector<set<int>> res =  {res1,res2,res3,res4,res5,res6,res7,res8,res9,res10,res11,res12};
   for (auto i = res.begin(); i != res.end(); i++)
    {
        

        outfile<<<< (*i).size()<< endl;
    }

    
    return 0;
}
