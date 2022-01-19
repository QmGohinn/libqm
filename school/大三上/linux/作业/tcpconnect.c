#include<stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define PORT 1234
#define MAXDATASIZE 100
    int main(int argc,char *argv[])
{
int sockfd,num;
char buf[MAXDATASIZE];

struct hostent *he;
struct sockaddr_in server;

if(argc != 2)
{

printf("usage: %s <ip address>\n",argv[0]);

exit(1);

}

if((he = gethostbyname(argv[1]))==NULL)
{
printf("gethostbyname() error\n");

exit(1);


}
if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)

{

printf("socket() error\n");

exit(1);

}
bzero(&server,sizeof(server));
server.sin_family=AF_INET;
server.sin_port=htons(PORT);
server.sin_addr=*((struct in_addr *)he->h_addr);
if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))==-1)
{
printf("connect() error\n");
exit(1);
}
if((num=recv(sockfd,buf,MAXDATASIZE,0))==-1)
{
printf("recv() error\n");
exit(1);
}
buf[num-1]='\0';
printf("server message:%s\n",buf);
close(sockfd);
}