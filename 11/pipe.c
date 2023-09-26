#include <stdio.h>
#include <unistd.h>

int main()
{
    int fds[2];
    pipe(fds);
    pid_t pid = fork();
    if(pid == 0)
    {
        printf("write ends \n");
        sleep(50);
        return 0;
    }
    else
    {
        write(fds[1],"I am child process",19);
        char msg[20];
        read(fds[0],msg,20);
        printf("recv message from pipe %s \n",msg);
        return 0;
    }
}
