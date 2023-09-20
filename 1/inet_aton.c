#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    char * addr = "127.0.0.1";
    struct sockaddr_in addr_inet;
    inet_aton(addr,&addr_inet.sin_addr);

    printf("addr_inet.sin_addr.s_addr :  %#xl \n",addr_inet.sin_addr.s_addr);

    return 0; 
}