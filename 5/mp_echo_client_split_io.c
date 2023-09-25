#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>


void clear_child(int sig)
{
    if(sig == SIGCHLD)
    {
        int status;
        pid_t pid = waitpid(-1,&status,WNOHANG);
        printf("clear child  process pid is %d \n",pid);
    }
}

int main(int argc,char*argv[])
{
    int clnt_sock = socket(PF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr1;
    memset(&addr1,0,sizeof(addr1));
    addr1.sin_family = AF_INET;
    addr1.sin_addr.s_addr = inet_addr(argv[1]);
    addr1.sin_port = htons(atoi(argv[2]));
    connect(clnt_sock,(struct sockaddr*)&addr1,sizeof(addr1));

    struct sigaction sigac;
    sigac.sa_handler = clear_child;
    sigemptyset(&sigac.sa_mask);
    sigac.sa_flags = 0;
    sigaction(SIGCHLD,&sigac,0);

    pid_t pid = fork();
    if(pid == 0)
    {
        char msg[20];
        while(1)
        {
            //printf("debug!!!\n");
            scanf("%s",msg);
            //printf("debug  1 !!! \n  %s\n",msg);
            if(msg[0] == 'q' || msg[0] == 'Q')
            {
                //printf("debug  2 !!!\n");
                shutdown(clnt_sock,SHUT_WR);
                printf("end child process \n");
                return 0;
            }
            else
                write(clnt_sock,msg,strlen(msg));
        }
    }
    else
    {
        char message[200]="123";
        int read_len=0;
        while((read_len = read(clnt_sock,message,200)) != 0)
            printf("recv message : %s \n",message);
        printf("end  father process \n");
        close(clnt_sock);
        return 0;
    }

}
