#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>


void clear_child(int sig)
{
    if(sig == SIGCHLD)
    {
        printf("clear child process ...\n");
        int status;
        pid_t pid = waitpid(-1,&status,WNOHANG);
        printf("remove child pid : %d \n child process return value : %d \n",pid,WEXITSTATUS(status));
    }
}

int main(int argc , char * argv[])
{

    struct sigaction sigac;
    sigac.sa_handler = clear_child;
    sigemptyset(&sigac.sa_mask);
    sigac.sa_flags = 0;
    sigaction(SIGCHLD,&sigac,0);
    int serv_sock = socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    listen(serv_sock,5);

    char msg[20];
    int strlen=0;

    while(1)
    {
        struct sockaddr_in clnt_addr;
        int clnt_addr_len=0;
        int clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len);
        if(clnt_sock != -1)
        {
            printf("connect!!!\n");
            pid_t pid = fork();
            if(pid == 0)
            {
                close(serv_sock);
                while((strlen = read(clnt_sock,msg,sizeof(msg)))!=0)
                    write(clnt_sock,msg,strlen);
                close(clnt_sock);
                return 0;//child process ends
            }
            else
            {
                printf("new child process : %d \n",pid);
                close(clnt_sock);
            }
        }
        else
            printf("connect fail\n");
    }
    return 0;

}