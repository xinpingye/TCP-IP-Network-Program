#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
    fd_set read_fd_set,tmp;
    FD_ZERO(&read_fd_set);
    FD_SET(0,&read_fd_set);
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 5000;

    while(1)
    {
        tmp = read_fd_set;
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;
        int result = select(1,&tmp,0,0,&timeout);
        if(result == -1)
            printf("error!!!\n");
        else if(result == 0)
            printf("time out !!!\n");
        else
        {
            if(FD_ISSET(0,&tmp))
            {
                char msg[20];
                int read_len = read(0,msg,20);
                printf("read message : %s \n",msg);
            }
        }
    }
}