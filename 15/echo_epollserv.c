#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
//#include <sys/select.h>
#include <sys/epoll.h>

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

    //fd_set reads,tmp;
    //struct timeval timeout;
    //int max_nums_monitor = serv_sock;

    //FD_ZERO(&reads);
    //FD_SET(serv_sock,&reads);
    int epfd = epoll_create(20);
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = serv_sock;
    epoll_ctl(epfd,EPOLL_CTL_ADD,serv_sock,&event);

    while(1)
    {
        //timeout.tv_sec = 5;
        //timeout.tv_usec = 5000;
        //tmp = reads;
        //int fd_nums = select(max_nums_monitor + 1,&tmp,0,0,&timeout);
        struct epoll_event* change_events = malloc(sizeof(struct epoll_event)*20);
        int fd_nums = epoll_wait(epfd,change_events,20,-1);
        if(fd_nums == 0)
        {
            printf("time out !!!\n next loop...\n");
            continue;
        }
        else
        {
            for(int i = 0;i < fd_nums;i++)
            {
                int fd_cur = change_events[i].data.fd;
                if(fd_cur == serv_sock)
                {
                    struct sockaddr_in clnt_addr;
                    int clnt_addr_len;
                    int clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len);
                    //FD_SET(clnt_sock,&reads);
                    //if(max_nums_monitor < clnt_sock)
                        //max_nums_monitor = clnt_sock;
                    struct epoll_event new_event;
                    new_event.events = EPOLLIN;
                    new_event.data.fd = clnt_sock;
                    epoll_ctl(epfd,EPOLL_CTL_ADD,clnt_sock,&new_event);
                    printf("new connect!!!\n");
                }
                else
                {
                    char buf[20];
                    int read_len = read(fd_cur,buf,sizeof(buf));
                    if(read_len == 0)
                    {
                        printf("disconnect with sock : %d \n",fd_cur);
                        close(fd_cur);
                        //FD_CLR(i,&reads);
                        epoll_ctl(epfd,EPOLL_CTL_DEL,fd_cur,NULL);
                    }
                    else
                    {
                        write(fd_cur,buf,read_len);
                        printf("recv message ; %s \n",buf);
                    }
                }
            }
            free(change_events);
        }
    }
    close(serv_sock);
    close(epfd);
    return 0;

}