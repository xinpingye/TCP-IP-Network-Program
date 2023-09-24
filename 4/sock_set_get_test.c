#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int sock = socket(PF_INET,SOCK_STREAM,0);
    int send_buf_len = 1024*3;
    int send_buf_len_len;
    int state = setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&send_buf_len,sizeof(send_buf_len));
    int recv_buf_len = 1024*3;
    int recv_buf_len_len;
    int state2 = setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&recv_buf_len,sizeof(recv_buf_len));
    printf("send buf len :%d \n recv buf len :%d \n",send_buf_len,recv_buf_len);
    state = getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&send_buf_len,&send_buf_len_len);
    state2 = getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&recv_buf_len,&recv_buf_len_len);
    printf("send buf len :%d \n recv buf len :%d \n",send_buf_len,recv_buf_len);
    return 0;

}