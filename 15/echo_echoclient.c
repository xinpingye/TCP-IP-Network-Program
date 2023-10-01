#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc,char*argv[])
{
    int clnt_sock = socket(PF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr1;
    memset(&addr1,0,sizeof(addr1));
    addr1.sin_family = AF_INET;
    addr1.sin_addr.s_addr = inet_addr(argv[1]);
    addr1.sin_port = htons(atoi(argv[2]));
    connect(clnt_sock,(struct sockaddr*)&addr1,sizeof(addr1));

    while(1)
    {
        char msg[20];
        scanf("%s",msg);
        printf("msg:%s\n",msg);
        if(msg[0] == 'q' || msg[0] == 'Q')
        { 
            close(clnt_sock);
            return 0;
        }
        else
        {
            char message[20]="123";
            write(clnt_sock,msg,strlen(msg));
            int read_len=0;
            while(read_len<strlen(msg))
                read_len += read(clnt_sock,message + read_len,20 - read_len);
            message[read_len]='0';
            printf("message : %s \n",message);
        }
    }
    return 0;
}