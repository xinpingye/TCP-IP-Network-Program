#include <stdio.h>
#include <pthread.h>

int sum = 0;

void* thread_sum(void* arg)
{
    int start = ((int*)arg)[0];
    int end = ((int*)arg)[1];
    while(start <= end)
    {
        sum += start;
        start++;
    }
    return NULL;
}

int main()
{
    pthread_t t_id1,t_id2;
    int range1[] = {1,5};
    int range2[] = {6,10};

    pthread_create(&t_id1,NULL,thread_sum,(void*)range1);
    pthread_create(&t_id2,NULL,thread_sum,(void*)range2);

    pthread_join(t_id1,NULL);
    pthread_join(t_id2,NULL);

    printf("sum is %d \n",sum);

    return 0;
}