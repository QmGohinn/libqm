#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
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
int main(int argc,char *argv[])
{
 int sockfd;
 char buf[BUFSIZE];
 struct sockaddr_in server_addr;
 struct hostent *host;
 int portnumber;
 int nbytes;
 int z=0;
 char reqBuf[BUFSIZE];
 if(argc!=3)
{
  fprintf(stderr,"Usage:%s hostname portnuber\a\n",argv[0]);
   exit(1);
}
if((host=gethostbyname(argv[1]))==NULL)
{
 fprintf(stderr,"Gethostname error \n");
exit(1);
}
if((portnumber=atoi(argv[2]))<0)
{
  fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]);
 exit(1);
}
if((sockfd=socket(PF_INET,SOCK_STREAM,0))==-1)
{
  fprintf(stderr,"Socket error:%s\a\n",strerror(errno));
 exit(1);
}
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(portnumber);
server_addr.sin_addr=*((struct in_addr *)host->h_addr);
if(connect(sockfd,(struct sockaddr*)(&server_addr),sizeof(server_addr))==-1)
{
 fprintf(stderr,"connect error : %s\a\n",strerror(errno));
 exit(1);
}
 printf("connected to server %s\n",inet_ntoa(server_addr.sin_addr));

 for(;;)
{
 memset(&reqBuf,0,sizeof(reqBuf));
 fputs("\nEnter a string(^D or 'qiut' to exit):",stdout);
if(!fgets(reqBuf,sizeof(reqBuf),stdin))
{
 printf("\n");
 break;
}
 printf(reqBuf);
 z=strlen(reqBuf);
 if(z>0&&reqBuf[--z]=='\n')
 reqBuf[z]=0;
 if(z==0)
 continue;
if(!strcasecmp(reqBuf,"QUIT"))
{
 printf("press an key to end client.\n");
 getchar();
 break;
}
 z=write(sockfd,reqBuf,strlen(reqBuf));
 printf("client has set'%s' to the server \n",reqBuf);
 if(z<0)
 bail("write()");
if((nbytes=read(sockfd,buf,sizeof(buf)))==-1)
{
 fprintf(stderr,"read() error:%s\n",strerror(errno));
 exit(1);
} 

 if(nbytes==0)
{
 printf("server hs closed the socket.\n");
 printf("press any key to exit...\n");
 getchar();
 break;
}
buf[nbytes]='\0';
 printf("result from %s port %u:the number of English lettters is%d\n",inet_ntoa(server_addr.sin_addr),(unsigned)ntohs(server_addr.sin_port),*(int *)(buf));
}
close(sockfd);
return 0;
}
