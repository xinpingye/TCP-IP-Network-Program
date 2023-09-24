#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        printf("child process 1\n");
        return 7;
    }
    else
    {
        printf("father process  my child process 1 pid is %d \n",pid);
        pid = fork();
        if(pid == 0)
        {
            printf("child process 2 \n");
            exit(8);
        }
        else
        {
            printf(" father process my child process 2 pid is %d \n",pid);
            int status;
            pid = wait(&status);
            printf("father clear my child zombie process and process id is %d \n child process return value : %d  \n",pid,WEXITSTATUS(status));
            sleep(40);
            pid = wait(&status);
            printf("father clear my child zombie process and process id is %d \n child process return value : %d  \n",pid,WEXITSTATUS(status));
            sleep(40);
            printf("father process ends\n");
        }
    }
    return 0;
}