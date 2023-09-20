#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    struct sockaddr_in addr1;
    char *port = "9110";
    memset(&addr1,0,sizeof(addr1));

    addr1.sin_family = AF_INET;
    addr1.sin_addr.s_addr = htonl(INADDR_ANY);
    addr1.sin_port = htons(atoi(port));

    printf("add1.sin_addr.s_addr : %#lx \n",addr1.sin_addr.s_addr);

    return 0;
}