#include"head.h"


int main()
{
    for(int i=0; i < 1048576; i++)
    {
        //cout<<i<<" "<<endl;
        int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(serv_sock < 0)
        {
            cout << "socket error"<<strerror(errno) << std::endl;
        }
        close(serv_sock);
    }
    
    return 0;
}