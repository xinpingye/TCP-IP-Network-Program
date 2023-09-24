#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>


pid_t pid;

void zombie_clear(int sig)
{
    if(sig == SIGCHLD)
    {
        printf("zonbir_clear method execute!!!\n");
        int status,return_value;
        sleep(20);
        printf("start clear zombie child process by waitpid api!!!\n");
        return_value = waitpid(pid,&status,WNOHANG);
        if(return_value!=0)
        {
            printf("father process clear zombie child process\n child process pid is %d \n  child return value is %d \n",pid,WEXITSTATUS(status));
            sleep(20);
        }
    }
}

int main()
{
    pid = fork();
    struct sigaction sigac;
    sigac.sa_handler = zombie_clear;
    sigemptyset(&sigac.sa_mask);
    sigac.sa_flags = 0;
    sigaction(SIGCHLD,&sigac,0);
    if(pid == 0)
    {
        printf("child process start sleep...\n");
        sleep(10);
        printf("child process here!!!\n");
        return 10;
    }
    else
    {
        printf("father process here \n my child process pid is %d \n father process start sleep...\n",pid);
        sleep(60);
        printf("father process ends!!!\n");
        return 0;
    }
}