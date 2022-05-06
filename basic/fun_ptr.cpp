#include "head.h"


double betsy(int);
double pam(int);
void estimate(int lines, double (*pf)(int));

int main() {
    int code;
    cin>>code;
    estimate(code,betsy);
    cout<<endl<<"next code: ";
    estimate(code,pam);

    return 0;
}

double betsy(int lns) {
    return 0.005 * lns;
}

double pam(int lns) {
    return 0.005 * lns * 2;
}

void estimate(int lines, double (*pf)(int)){
    cout<<lines<<"lines will take"<<endl;

    cout<<(*pf)(lines)<<endl;
}