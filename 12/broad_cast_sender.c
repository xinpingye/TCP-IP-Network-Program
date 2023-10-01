#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc , char * argv[])
{
    //printf("debug1\n");
    int send_sock = socket(PF_INET,SOCK_DGRAM,0);
    //printf("debug2\n");
    struct sockaddr_in dst_addr;
    memset(&dst_addr,0,sizeof(dst_addr));
    dst_addr.sin_family = AF_INET;
    dst_addr.sin_addr.s_addr = inet_addr(argv[1]);
    dst_addr.sin_port = htons(atoi(argv[2]));
    int broad_cast_set = 1;
    //printf("debug3\n");
    setsockopt(send_sock,SOL_SOCKET,SO_BROADCAST,(void*)&broad_cast_set,sizeof(broad_cast_set));
    FILE*fp = fopen("news.txt","r");

    //printf("debug4\n");
    while(!feof(fp))
    {
        char buf[20];
        fgets(buf,20,fp);
        printf("send str : %s \n",buf);
        sendto(send_sock,buf,20,0,(struct sockaddr*)&dst_addr,sizeof(dst_addr));
        sleep(2);
    }

    fclose(fp);
    close(send_sock);
    return 0;
}