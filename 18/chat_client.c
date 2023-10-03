#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

void* send_msg(void* arg)
{
    int sock = *((int*)arg);
    char msg[100];
    while(1)
    {
        fgets(msg,100,stdin);
        if(!strcmp(msg,"q\n")||!strcmp(msg,"Q\n"))
        {
            
            close(sock);
            exit(0);
        }
        else
            write(sock,msg,strlen(msg));
    }
    return NULL;
}

void* recv_msg(void* arg)
{
    int sock = *((int*)arg);
    char msg[100];
    while(1)
    {
        int str_len = read(sock,msg,100);
        if(str_len == 0)
            return NULL;
        printf("recv msg : %s \n",msg);
    }
    return NULL;
}

int main(int argc,char*argv[])
{
    int clnt_sock = socket(PF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr1;
    memset(&addr1,0,sizeof(addr1));
    addr1.sin_family = AF_INET;
    addr1.sin_addr.s_addr = inet_addr(argv[1]);
    addr1.sin_port = htons(atoi(argv[2]));
    connect(clnt_sock,(struct sockaddr*)&addr1,sizeof(addr1));

    pthread_t t_id1,t_id2;
    pthread_create(&t_id1,NULL,send_msg,(void*)&clnt_sock);
    pthread_create(&t_id2,NULL,recv_msg,(void*)&clnt_sock);

    pthread_join(t_id1,NULL);
    //close(clnt_sock);
    pthread_join(t_id2,NULL);
    return 0;
}