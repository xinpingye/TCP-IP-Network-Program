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
            printf("debug\n");
            struct hostent * host_info_for_name = gethostbyaddr(*ip_list,4,AF_INET);
            printf("debug1\n");
            
            if(host_info_for_name->h_aliases==NULL)
            {
                printf("debug!!!\n");
            }
            else
                printf("debug!!!!!!\n");
            /*
            printf("debug2\n");
            while((*h_aliases)!=NULL)
            {
                printf("debug3\n");
                printf("alias : %s\t",*h_aliases);
                h_aliases++;
            }
            */
            printf("\n");
            ip_list++;
        }
    }
    return 0;
}