#include "head.h"

int main() {
    union {
        short value;
        char  bytes[sizeof(short)];
    }test;
    test.value = 0x0102;
    if(test.bytes[0] == 1 && test.bytes[1] == 2){
        cout<<"大端机器"<<endl;
    }
    else if(test.bytes[0] == 2 && test.bytes[1] == 1){
        cout<<"小端机器"<<endl;
    }
    else{
        cout<<"未知"<<endl;
    }

    return 0;
}