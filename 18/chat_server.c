#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

int clnt_cnt = 0;
int clnt_socks[256];
pthread_mutex_t mutex;

void send_msg(char* msg,int len)
{
    int i;
    pthread_mutex_lock(&mutex);
    for(i = 0;i < clnt_cnt;i++)
        write(clnt_socks[i],msg,len);
    pthread_mutex_unlock(&mutex);
}

void* handle_clnt(void* arg)
{
    printf("I start!!!\n");
    int clnt_sock = *((int*)arg);
    printf("clnt_sock : %d \n",clnt_sock);
    int str_len = 0;
    char msg[100];

    while((str_len = read(clnt_sock,msg,sizeof(msg))) != 0)
        send_msg(msg,str_len);
    printf("debug!!!\n");
    pthread_mutex_lock(&mutex);
    for(int i = 0;i < clnt_cnt;i++)
    {
        if(clnt_sock == clnt_socks[i])
        {
            while(i++ < clnt_cnt - 1)
                clnt_socks[i] = clnt_socks[i+1];
            break;
        }
    }
    clnt_cnt--;
    pthread_mutex_unlock(&mutex);
    close(clnt_sock);
    printf("remove a connect!!!\n");
    return NULL;
}

int main(int argc , char * argv[])
{
    int serv_sock = socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    listen(serv_sock,5);

    while(1)
    {
        struct sockaddr_in clnt_addr;
        int clnt_addr_len = sizeof(clnt_addr);
        int clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len);

        pthread_mutex_lock(&mutex);
        clnt_socks[clnt_cnt++] = clnt_sock;
        pthread_mutex_unlock(&mutex);

        pthread_t t_id;
        pthread_create(&t_id,NULL,handle_clnt,&clnt_sock);
        pthread_detach(t_id);
        printf("new connect established and thread start!!!\n");

    }
    close(serv_sock);
    return 0;
}