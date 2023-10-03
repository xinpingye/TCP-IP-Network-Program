#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>


char* content_type(char* file)
{
    char extension[100];
    char file_name[100];
    strcpy(file_name,file);
    strtok(file_name,".");
    strcpy(extension,strtok(NULL,"."));
    if(!strcmp(extension,"html")||!strcmp(extension,"htm"))
        return "text/html";
    else
        return "text/plain";
}

void send_error(FILE* fp)
{
    char protocol[] = "HTTP/1.0 400 Bad Request\r\n";
    char server[] = "Server:Linux Web Server \r\n";
    char cnt_len[] = "Content-length:2048\r\n"; 
    char cnt_type[] = "Content-type:text/html\r\n\r\n";
    char content[] = "<html><head><title>NETWORK</title></head>"
    "<body><front size=+5><br>wrong!!!"
    "</front>></body></html>";
    fputs(protocol,fp);
    fputs(server,fp);
    fputs(cnt_len,fp);
    fputs(cnt_type,fp);
    fputs(content,fp);
    fflush(fp);
}

void send_data(FILE* fp,char* ct,char* filename)
{
    char protocol[] = "HTTP/1.0 200 OK\r\n";
    char server[] = "Server:Linux Web Server \r\n";
    char cnt_len[] = "Content-length:2048\r\n";
    char cnt_type[100];
    sprintf(cnt_type,"Content-type:%s\r\n\r\n",ct);
    FILE* send_file = fopen(filename,"r");
    printf("filename : %s \n",filename);
    if(send_file == NULL)
    {
        send_error(fp);
        return;
    }

    fputs(protocol,fp);
    fputs(server,fp);
    fputs(cnt_len,fp);
    fputs(cnt_type,fp);

    char buf[1024];
    while(fgets(buf,1024,send_file)!=NULL)
    {
        fputs(buf,fp);
        fflush(fp);
    }
    fflush(fp);
    fclose(fp);

}

void* request_handler(void* arg)
{
    int clnt_sock = *((int*)arg);
    char req_line[100];
    printf("debug!!!\n");
    FILE* read_clnt = fdopen(clnt_sock,"r");
    FILE* write_clnt = fdopen(dup(clnt_sock),"w");
    fgets(req_line,100,read_clnt);
    printf("req_line : %s \n",req_line);
    if(strstr(req_line,"HTTP/") == NULL)
    {
        send_error(write_clnt);
        fclose(read_clnt);
        fclose(write_clnt);
        return NULL;
    }
    char method[100];
    strcpy(method,strtok(req_line," /"));
    char filename[100];
    strcpy(filename,strtok(NULL," /"));
    char ct[100];
    strcpy(ct,content_type(filename));
    if(strcmp(method,"GET")!=0)
    {
        send_error(write_clnt);
        fclose(read_clnt);
        fclose(write_clnt);
        return NULL;
    }
    fclose(read_clnt);
    send_data(write_clnt,ct,filename);
    return NULL;
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

    while(1)
    {
        struct sockaddr_in clnt_addr;
        int clnt_addr_len = sizeof(clnt_addr);
        int clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len);

        pthread_t t_id;
        pthread_create(&t_id,NULL,request_handler,&clnt_sock);
        pthread_detach(t_id);
    }
    close(serv_sock);
    return 0;
}


