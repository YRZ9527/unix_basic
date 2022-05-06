#include "head.h"
#include "math.h"

using namespace std;

struct polar{
    double distance;
    double angle;
};

struct rect
{
    double x;
    double y;
};


void rect_to_polor(const rect* pxy, polar* pda);
void show_polar(const polar* pda);

int main() {
    rect rplace;
    polar pplace;

    cout<<"================"<<"enter x and y"<<endl;
    while(cin>>rplace.x>>rplace.y)
    {
        rect_to_polor(&rplace,&pplace);
        show_polar(&pplace);
        cout<<"next two numbers(q to quit)"<<endl;
    }
    cout<<"done"<<endl;
    return 0;

    return 0;
}


void show_polar(const polar* pda) {
    const double Rad_to_deg = 798.12121231;
    cout<<"distance"<<pda->distance<<endl;
    cout<<"angle"<<pda->angle<<endl;
    cout<<"degrees"<<endl;
}

void rect_to_polor(const rect* pxy, polar* pda) {
    pda->distance = sqrt(pxy->x*pxy->x + pxy->y*pxy->y);
    pda->angle = atan2(pxy->y,pxy->x);
}