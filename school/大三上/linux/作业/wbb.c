#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define BUFSIZE 512
static void bail(const char *on_what)

{
fputs(strerror(errno),stderr);
fputs(":",stderr);
fputs(on_what,stderr);
fputc('\n',stderr);

exit(1);

}

int main(int argc,char **argv)
{
long z;
int sockfd;
char *srv_addr=NULL;
struct sockaddr_in server_addr;
struct sockaddr_in_addr;
int portnumber;
char dgram[BUFSIZE];
srv_addr=argv[1];
if((portnumber=atoi(argv[2]))<0);
{
fprintf(stderr,"error");
exit(1);

}

memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(portnumber);

if(!inet_aton(srv_addr,&server_addr.sin_addr))
bail("bad address");

sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd==-1)
bail("socket"());
for(;;)
{
fputs("\nEnter a string:",stdout);
if(!fgets(dgram,sizeof(dgram),stdin))
break;
z=strlen(dgram);
if(z>0&&dgram[--z]=='\n')
dgram[z]=0,
if(z==0)
continue;
z=sendto(sockfd,dgram,strlen(dgram),0,(struct sockaddr*)&server_addr,sizeof(server_addr));
if(z<0)
bail("sendto()");
printf("send %s to the server\n",dgram);
if(!strcasecmp(dgram,"QUIT"))
break;
socklen_t size=sizeof(_addr);
int num;
z=recvfrom(sockfd,&num,sizeof(int),0,(struct sockaddr*)&_addr,&size);
if(z<0)
bail("recvfrom()");
dgram[z]=0;
printf("result from %s port %u:the number of english letters is %d\n",inet_ntoa(_addr.sin_addr),ntohs(_addr.sin_port),num);


}
printf("\n exits from loop.\n");
close(sockfd);
return 0;


}