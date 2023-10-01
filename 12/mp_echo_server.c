#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <sys/select.h>


int main(int argc , char * argv[])
{
    int serv_sock = socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    listen(serv_sock,5);

    fd_set reads,tmp;
    struct timeval timeout;
    int max_nums_monitor = serv_sock;

    FD_ZERO(&reads);
    FD_SET(serv_sock,&reads);

    while(1)
    {
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;
        tmp = reads;
        int fd_nums = select(max_nums_monitor + 1,&tmp,0,0,&timeout);
        if(fd_nums == 0)
        {
            printf("time out !!!\n next loop...\n");
            continue;
        }
        else
        {
            for(int i = 0;i <= max_nums_monitor;i++)
            {
                if(FD_ISSET(i,&tmp))
                {
                    if(i == serv_sock)
                    {
                        struct sockaddr_in clnt_addr;
                        int clnt_addr_len;
                        int clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len);
                        FD_SET(clnt_sock,&reads);
                        if(max_nums_monitor < clnt_sock)
                            max_nums_monitor = clnt_sock;
                        printf("new connect!!!\n");
                    }
                    else
                    {
                        char buf[20];
                        int read_len = read(i,buf,sizeof(buf));
                        if(read_len == 0)
                        {
                            printf("disconnect with sock : %d \n",i);
                            close(i);
                            FD_CLR(i,&reads);
                        }
                        else
                        {
                            write(i,buf,read_len);
                            printf("recv message ; %s \n",buf);
                        }
                    }
                }
            }
        }
    }
    close(serv_sock);
    return 0;

}