#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    struct sockaddr_in addr1;
    char * addr2 = "127.0.0.1";
    inet_aton(addr2,&addr1.sin_addr);

    char * addr3 = inet_ntoa(addr1.sin_addr);
    char addr4[20];
    strcpy(addr4,addr3);

    printf("addr4: %s\n",addr4);

    return 0;
}