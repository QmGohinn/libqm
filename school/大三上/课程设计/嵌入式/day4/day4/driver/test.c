#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

#include <unistd.h>
#include "mycmd.h"


int main()
{
	int fd;
	char  buf[20] = {0};
	int len;

	fd = open("/dev/hello", O_RDWR);
	printf("application open\n");
	if(fd < 0 )
		return -1;

	
	getchar();
	ioctl(fd, PLAY_TONE, 400);
	sleep(1);
	printf("application send PLAY_TONE\n");

	getchar();

	
	ioctl(fd, PLAY_STOP);
	printf("application send PLAY_STOP\n");

	getchar();
	close(fd);
	printf("application close\n");
	return 0;
	
}
