#include <stdio.h>
#include <fcntl.h>

int main()
{
    FILE* fd1 = fopen("data.txt","r");
    int fd2 = fileno(fd1);
    char buf[20];
    int len = read(fd2,buf,20);
    printf("read message from file : %s ",buf);
    return 0;
}