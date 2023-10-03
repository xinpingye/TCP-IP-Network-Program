#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

static sem_t sem_one;
static sem_t sem_two;
static int num;

void* read(void* arg)
{
    int i;
    for(i = 0;i < 5;i++)
    {
        fputs("input num :  ",stdout);
        sem_wait(&sem_two);
        scanf("%d",&num);
        sem_post(&sem_one);
    }
    return NULL;
}

void* accu(void* arg)
{
    int sum = 0,i;
    for(i = 0;i < 5;i++)
    {
        sem_wait(&sem_one);
        sum += num;
        sem_post(&sem_two);
    }
    printf("result : %d \n",sum);
    return NULL;
}

int main()
{
    pthread_t t_id1,t_id2;
    sem_init(&sem_one,0,0);
    sem_init(&sem_two,0,1);

    pthread_create(&t_id1,NULL,read,NULL);
    pthread_create(&t_id2,NULL,accu,NULL);

    pthread_join(t_id1,NULL);
    pthread_join(t_id2,NULL);

    sem_destroy(&sem_one);
    sem_destroy(&sem_two);
    
    return 0;
}