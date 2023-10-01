#include <stdio.h>

int main()
{
    FILE* fd1 = fopen("news.txt","r");
    FILE* fd2 = fopen("cpy.txt","w");
    char buf[20];
    int len = 0;
    while(fgets(buf,20,fd1)!=NULL)
        fputs(buf,fd2);
    fclose(fd1);
    fclose(fd2);
    return 0;
}