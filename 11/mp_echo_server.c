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

//#define STR(s)  #s


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
            int fds[2];
            pipe(fds);
            printf("connect!!!\n");
            pid_t pid = fork();
            if(pid == 0)
            {
                close(serv_sock);
                close(clnt_sock);
                time_t t;
                time(&t);
                char *ch = ctime(&t);
                int fd = open("data.txt",O_CREAT|O_WRONLY|O_TRUNC);
                printf("debug!!!\n");
                char msg[20];
                int read_len;
                while(1)
                {
                    printf("debug 1 !!!\n");
                    read_len = read(fds[0],msg,20);
                    printf("recv msg from another process : %s \n",msg);
                    write(fd,msg,read_len);
                    memset(msg,0,sizeof(msg));
                }

            }
            else
            {
                printf("new child process : %d \n",pid);
                //close(clnt_sock);
                pid_t pid1 = fork();
                if(pid1 == 0)
                {
                    close(serv_sock);
                    while((strlen = read(clnt_sock,msg,sizeof(msg)))!=0)
                    {
                        write(clnt_sock,msg,strlen);
                        write(fds[1],msg,strlen);
                        printf("write msg :%s \n",msg);
                    }
                    close(clnt_sock);
                    return 0;//child process ends
                }
                else
                {
                    close(clnt_sock);
                    printf("next loop...\n");
                }
            }
        }
        else
            printf("connect fail\n");
    }
    close(serv_sock);
    return 0;

}