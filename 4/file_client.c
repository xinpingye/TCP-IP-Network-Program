#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc , char * argv[])
{
    FILE* fp = fopen("recv.txt","wb");
    int clnt_sock = socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(atoi(argv[1]));
    connect(clnt_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    int read_cnt;
    int file_read_buf[30];
    while((read_cnt = read(clnt_sock,file_read_buf,30))!=0)
        fwrite(file_read_buf,1,read_cnt,fp);
    char message[30] = "Thank you!!!\n";
    write(clnt_sock,message,strlen(message));
    fclose(fp);
    close(clnt_sock);
    return 0;
}