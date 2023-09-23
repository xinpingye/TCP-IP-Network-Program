#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc , char * argv[])
{
    int clnt_sock = socket(PF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    char message[20] = "hello udp \n"; 
    sendto(clnt_sock,message,20,0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    char msg[20];
    int serv_addr_len;
    printf("debug\n");

    struct sockaddr_in clnt_addr;
    memset(&clnt_addr,0,sizeof(clnt_addr));
    int clnt_addr_len;
    int recv_len = recvfrom(clnt_sock,msg,20,0,(struct sockaddr*)&clnt_addr,&clnt_addr_len);
    printf("recv msg : %s \n",msg);
    return 0;

}