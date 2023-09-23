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
    sendto(clnt_sock,message,20,0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    sendto(clnt_sock,message,20,0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    printf("sendto finished!!!\n");
    close(clnt_sock);
    return 0;
}