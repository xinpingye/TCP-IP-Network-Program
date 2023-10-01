#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc , char * argv[])
{
    int recv_sock = socket(PF_INET,SOCK_DGRAM,0);
    struct sockaddr_in recv_addr;
    memset(&recv_addr,0,sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_addr.sin_port = htons(atoi(argv[2]));
    bind(recv_sock,(struct sockaddr*)&recv_addr,sizeof(recv_addr));
    //printf("debug1\n");
    struct ip_mreq join_adr;
    join_adr.imr_multiaddr.s_addr = inet_addr(argv[1]);
    join_adr.imr_interface.s_addr = htonl(INADDR_ANY);
    //printf("debug2\n");
    setsockopt(recv_sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,(void*)&join_adr,sizeof(join_adr));
    //printf("debug3\n");
    while(1)
    {
        //printf("debug4\n");
        char buf[20];
        int str_len = recvfrom(recv_sock,buf,20 - 1,0,NULL,0);
        //printf("debug5\n");
        printf("str:%s\n",buf);
        if(str_len < 0 )
            break;
        fputs(buf,stdout);
    }
    close(recv_sock);
    return 0;
}