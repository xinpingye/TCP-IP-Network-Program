#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc , char * argv[])
{
    struct hostent * host_info = gethostbyname(argv[1]);
    if(host_info->h_addrtype == AF_INET)
    {
        char ** ip_list = host_info->h_addr_list;
        while((*ip_list)!=NULL)
        {
            printf("ip : %s \n",inet_ntoa(*((struct in_addr*)(*ip_list))));
            ip_list++;
        }
    }
    return 0;
}