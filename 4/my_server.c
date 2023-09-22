#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int nums_str_to_num(char*nums,int offset,int nums_len)
{
    int result = 0;
    for(int i = offset;i < offset + nums_len;i++)
    {
        result *= 10;
        result += nums[i] - '0';
    }
    return result;
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

    printf("begin loop!!!\n");

    while(1)
    {
        struct sockaddr_in clnt_addr;
        int clnt_addr_len=0;
        int clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len);
        printf("new connect!!!\n");

        char message[200];
        int read_len = 0;
        int pos = 0;
        while(1)
        {
            int tmp_read_len = 0;
            tmp_read_len = read(clnt_sock,&message[read_len],200-read_len);
            read_len +=tmp_read_len;
            int find_result = 0;
            //printf("debug1 !!!\n");
            printf("read_len:%d\n",read_len);
            while(pos < read_len)
            {
                //printf("debug2 !!!\n");
                if(message[pos] == '+' || message[pos] == '-' || message[pos] == '*' || message[pos] == '/')
                {
                    //printf("debug3 !!!\n");
                    find_result = 1;
                    break;           
                }
                else
                    pos++;
            }
            //printf("debug4 !!!\n");
            if(find_result == 1)
                break;
        }
        //printf("debug5 !!!\n");
        int find_1_result = 0;
        while(1)
        {
            if(pos + 1 <read_len)
            {
                if(message[++pos] == ' ')
                {
                    find_1_result = 1;
                    break;
                }
                else
                {
                    printf("something error!!!\n");
                    break;
                }
            }
            else
            {
                int tmp_read_len = 0;
                tmp_read_len = read(clnt_sock,&message[read_len],200-read_len);
                read_len +=tmp_read_len;
            }
        }
        //printf("debug6 !!!\n");
        int nums_begin = 0;
        int nums_end = 0;

        if(find_1_result == 1)
        {
            while(1)
            {
                if(pos + 1 <read_len)
                {
                    //printf("debug7 !!!\n");
                    ++pos;
                    if('0'<= message[pos] && message[pos] <= '9')
                    {
                        //printf("debug8 !!!\n");
                        nums_begin = pos;
                        while(1)
                        {
                            if(!(pos + 1 <read_len))
                            {
                                int tmp_read_len = 0;
                                tmp_read_len = read(clnt_sock,&message[read_len],200-read_len);
                                read_len +=tmp_read_len;
                            }
                            else
                            {
                                //printf("debug9 !!!\n");
                                ++pos;
                                if('0'<= message[pos] && message[pos] <= '9')
                                    continue;
                                else if(message[pos] == ' ')
                                {
                                    //printf("debug10 !!!\n");
                                    nums_end = pos;
                                    break;
                                }
                                else
                                {
                                    printf("something error!!!\n");
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
                else
                {
                    int tmp_read_len = 0;
                    tmp_read_len = read(clnt_sock,&message[read_len],200-read_len);
                    read_len +=tmp_read_len; 
                }
            }
            //printf("debug11 !!!\n");
        }
        printf("nums_begin:%d nums_end:%d\n",nums_begin,nums_end);
        if(nums_end)
        {
            int result = nums_str_to_num(message,nums_begin,nums_end-nums_begin);
            printf("messgae.nums:%d\n",result);
        }
        //printf("debug12 !!!\n");
        close(clnt_sock);
        printf("end connect!!!\n");
       
    }
    return 0;
}