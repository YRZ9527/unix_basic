#include "iostream"

using namespace std;


int main()

{
    double R1 = 38800000;
    double R2 = 24100000;
    double R3 =380000000;
    double E1 = 150;
    double E2 = 1;
    double Ap1 = 0.025 * 0.025;
    double Ap2 = 3.7 * 3.7 * 0.08;
    double temp1 = (E1 * Ap1) / (R1 * R1);
    double temp2 = (E2 * Ap2) / (R3 * R3);
    double temp = temp1 / temp2;

    double res = 4.4 /temp;

    cout<<temp <<endl;
    cout<<"res = "<< res<<endl;
}