#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd1 = open("data.txt",O_WRONLY|O_TRUNC);
    FILE* fd2 = fdopen(fd1,"w");
    fputs("1234567\n",fd2);
    fclose(fd2);
    return 0;
}