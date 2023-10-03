#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void* thread_main(void* arg)
{
    int i;
    int cnt = *((int*)arg);
    char* msg = (char*)malloc(sizeof(char)*50);
    strcpy(msg,"hello I am thread!!!\n");
    for(int i = 0;i<cnt;i++)
    {
        sleep(1);
        puts("running thread");
    }
    return (void*)msg;
}

int main()
{
    pthread_t t_id;
    int thread_param = 5;
    pthread_create(&t_id,NULL,thread_main,(void*)&thread_param);
    void* t_ret;
    pthread_join(t_id,&t_ret);
    printf("thread return value : %s \n",(char*)t_ret);
    free(t_ret);
    return 0;
}