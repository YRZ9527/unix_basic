#include"head.h"


const double (*f1)(const double ar[], int n);
const double (*f2)(const double [], int );
const double (*f3)(const double* , int );

int main() {
    double av[3] = {11.212,3.212,226.9};

    const double *(*p1)(const double* ,int) = f1;
    
    //use c++ 11
    auto p2 = f2;
    const double (*p3)(const double)




    return 0;
}