#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORT 1234
#define BACKLOG 1
socklen_t len;
int main()
{
int listenfd,connectfd;


struct sockaddr_in server;
struct sockaddr_in client;
socklen_t addrlen;
if ((listenfd = socket(AF_INET,SOCK_STREAM,0))==-1)

{
perror("socket() error.");

exit(1);
}
int opt=SO_REUSEADDR;
setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
bzero(&server,sizeof(server));
server.sin_family=AF_INET;
server.sin_port=htons(PORT);
server.sin_addr.s_addr=htonl (INADDR_ANY);
if(bind(listenfd,(struct sockaddr *)&server,sizeof(server))==-1)
{
perror("Bind() error");
exit(1);
}
if(listen(listenfd,BACKLOG)==-1)
{
perror("listen() error.\n");
exit(1);
}
len=sizeof(client);
if((connectfd=accept(listenfd,(struct sockaddr*)&client,&addrlen))==-1)
{
perror("accept() error\n");
exit(1);
}
printf("You got a connection from client's ip is %s,port is %d\n",inet_ntoa(client.sin_addr),htons(client.sin_port));

send(connectfd,"Welcome\n",8,0);
close(connectfd);
close(listenfd);
}