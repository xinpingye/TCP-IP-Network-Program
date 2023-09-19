#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buf[] = "Let's go\n\r";

    fd = open("data.txt",O_CREAT|O_WRONLY|O_TRUNC);

    printf("file description: %d \n",fd);

    write(fd,buf,sizeof(buf));

    close(fd);

    return 0;
}