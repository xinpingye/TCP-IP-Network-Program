#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid =fork();

    if(pid == 0)
    {
        printf(" Hi I am child process\n");
    }
    else
    {
        printf("father process my child pid is :%d \n",pid);
        sleep(30);
    }
    if(pid == 0)
        printf("child process ends \n");
    else
        printf("father process ends \n");
    return 0;
}