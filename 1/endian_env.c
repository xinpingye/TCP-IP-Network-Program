#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("host_port : %x \n net_port : %x \n  host_addr : %lx \n net_addr : %lx \n",host_port,net_port,host_addr,net_addr);

    return 0;
}