#include <stdio.h>
#include <unistd.h>

int main()
{
    int fds1[2],fds2[2];
    pipe(fds1);
    pipe(fds2);
    pid_t pid = fork();

    if(pid == 0)
    {
        write(fds1[1],"I am child process\n",20);
        char msg[30];
        read(fds2[0],msg,30);
        printf(" child recv meg from pipe : %s \n",msg);
        return 0;
    }
    else
    {
        char msg[30];
        read(fds1[0],msg,30);
        printf("father process recv message from child process : %s \n",msg);
        write(fds2[1],"I am your father\n",18);
        printf("father process ends!!!\n");
        return 0;
    }
}