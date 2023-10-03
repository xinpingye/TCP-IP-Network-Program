#include <stdio.h>
#include <pthread.h>

int NumSize = 100;

int sum = 0;

pthread_mutex_t mutex;

void* des(void* arg)
{
    int i = 0;
    pthread_mutex_lock(&mutex);
    for(;i < 50000000;i++)
    {
        
        sum+=1;
        
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* inc(void* arg)
{
    int i = 0;
    pthread_mutex_lock(&mutex);
    for(;i < 50000000;i++)
    {
        
        sum-=1;
        
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_t t_id_array[NumSize];
    pthread_mutex_init(&mutex,NULL);
    for(int i = 0 ;i < NumSize;i++)
    {
        if(i%2)
            pthread_create(&t_id_array[i],NULL,des,NULL);
        else
            pthread_create(&t_id_array[i],NULL,inc,NULL);
    }
    for(int i = 0;i < NumSize;i++)
        pthread_join(t_id_array[i],NULL);
    printf("sum is %d \n",sum);
    pthread_mutex_destroy(&mutex);
    return 0;
}