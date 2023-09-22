#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc , char * argv[])
{
    int clnt_sock = socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    int serv_addr_len = 0;
    connect(clnt_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    char  message[20] = "   * 123456 ...";
    write(clnt_sock,message,strlen(message));
    sleep(20);
    close(clnt_sock);
    return 0;

}