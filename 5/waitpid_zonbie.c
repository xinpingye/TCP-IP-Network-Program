#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        printf(" child process begin sleep!!! \n");
        sleep(30);
        return 8;
    }
    else
    {
        printf("father process my child process pid is %d \n",pid);
        printf("loop start!!!\n");
        int return_value;
        int status;
        while((return_value = waitpid(pid,&status,WNOHANG))==0)
        {
            printf("father sleep 5s\n");
            sleep(5);
        }
        printf("father process my child process id : %d \n my child process return value : %d \n",pid,WEXITSTATUS(status));
        sleep(30);
        printf("father process ends \n");
        return 0;
    }
}