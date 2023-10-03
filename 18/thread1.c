#include <stdio.h>
#include <pthread.h>

void* thread_main(void* arg)
{
    int i;
    int cnt = *((int*)arg);
    for(int i = 0;i<cnt;i++)
    {
        sleep(2);
        puts("running thread");
    }
    return NULL;
}

int main()
{
    pthread_t t_id;
    int thread_param = 5;
    pthread_create(&t_id,NULL,thread_main,(void*)&thread_param);
    sleep(10);
    puts("end of main");
    return 0;
}