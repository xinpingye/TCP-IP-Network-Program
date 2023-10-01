#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd1 = open("news.txt",O_RDONLY);
    int fd2 = open("cpy.txt",O_WRONLY|O_CREAT|O_TRUNC);
    char buf[20];
    int len = 0;
    while((len = (read(fd1,buf,20))) > 0)
        write(fd2,buf,len);
    close(fd1);
    close(fd2);
    return 0;
}