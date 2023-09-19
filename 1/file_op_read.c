#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    fd = open("data.txt",O_RDONLY);
    char buf [32];
    int str_len = read(fd,buf,sizeof(buf));
    printf("data.txt:%s\n",buf);
    return 0;

}