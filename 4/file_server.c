#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc , char * argv[])
{
    FILE* fp = fopen("../test.c","rb");
    int serv_sock = socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    listen(serv_sock,5);
    struct sockaddr_in clnt_addr;
    int clnt_addr_len;
    int clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len);
    char file_read_buf[30];
    while(1)
    {
        int read_cnt = fread((void*)file_read_buf,1,sizeof(file_read_buf),fp);
        if(read_cnt < 30)
        {
            printf("last write\n");
            write(clnt_sock,file_read_buf,read_cnt);
            break;
        }
        else
        {
             write(clnt_sock,file_read_buf,read_cnt);
        }
    }

    shutdown(clnt_sock,SHUT_WR);
    read(clnt_sock,file_read_buf,30);
    printf("recv message : %s \n",file_read_buf);
    close(clnt_sock);
    close(serv_sock);
    fclose(fp);
    return 0;

}