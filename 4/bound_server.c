#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc , char * argv[])
{
    int serv_sock = socket(PF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv_addr,clnt_addr;
    int clnt_addr_size;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    for(int i=0;i<3;i++)
    {
        sleep(5);
        char message[20];
        int recv_len = recvfrom(serv_sock,message,20,0,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
        printf("loop : %d  recv message : %s \n",i,message);
    }
    close(serv_sock);
    return 0;
}