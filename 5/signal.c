#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void key_control(int sig)
{
    if(sig == SIGINT)
        printf("key control method excute!!!\n");
}


void alarm_control(int sig)
{
    if(sig == SIGALRM)
        printf("alarm control method excute!!!\n");
}

int main()
{
    struct sigaction sigac;
    sigac.sa_handler = alarm_control;
    sigemptyset(&sigac.sa_mask);
    sigac.sa_flags = 0;
    sigaction(SIGALRM,&sigac,0);
    signal(SIGINT,key_control);
    alarm(10);
    for(int i = 0;i<3;i++)
    {
        printf("shall sleeping 100\n");
        sleep(100);
    }
    return 0;
}