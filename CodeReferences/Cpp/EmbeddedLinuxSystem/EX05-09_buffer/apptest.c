#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "my_ioctl.h"

#define RBUF_MAX 100

int main(int argc, char *argv[])
{
	int fd, len, rlen, wlen;
	char rbuf[RBUF_MAX];
	char *wbuf;
	char *devname = argv[1];

	if(argc != 4) {
		printf("usgage: %s {device file} {R|W|I} {option}\n", argv[0]);
		return -1;
	}

	fd = open(devname, O_RDWR);
	if(fd < 0) {
		printf("apptest: can't open %s\n", devname);
		return -1;
	}
	printf("apptest: %s opened\n", devname);
	fflush(stdout);

	if(strcmp(argv[2], "R") == 0) {
		len = atoi(argv[3]);
		if(len > (RBUF_MAX-1)) {
			printf("apptest: read size is too big(can be read up to %d\n", RBUF_MAX-1);
			return -1;
		}

		rlen = read(fd, rbuf, len);
		if(rlen == -1) {
			printf("apptest: can't read\n");
			return -1;
		}
		rbuf[rlen] = 0;
		printf("apptest: %d bytes read [%s]\n", rlen, rbuf);
	} 
	else if(strcmp(argv[2], "W") == 0) {
		wbuf = argv[3];
		len = strlen(wbuf);

		wlen = write(fd, wbuf, len);
		if(wlen == -1) {
			printf("apptest: can't write\n");
			return -1;
		}
		wbuf[wlen] = 0;
		printf("apptest: %d bytes written [%s]\n", wlen, wbuf);
	}
	else if(strcmp(argv[2], "I") == 0) {
		int ret;
		int arg;

		if(strcmp(argv[3], "1") == 0) {
			printf("apptest: call ioctl() with MY_IOCTL_CMD_CLEAR_BUF\n");
			ret = ioctl(fd, MY_IOCTL_CMD_CLEAR_BUF);
			printf("apptest: return value is %d\n", ret);
		}
		else if(strcmp(argv[3], "2") == 0) {
			printf("apptest: call ioctl() with MY_IOCTL_CMD_GET_FREE_BUF_SIZE\n");
			ret = ioctl(fd, MY_IOCTL_CMD_GET_FREE_BUF_SIZE, &arg);
			printf("apptest: return value is %d\n", ret);
			if(!ret) printf("apptest: free buffer size is %d\n", arg);
		}
		else {
			printf("apptest: call ioctl() with unknown command\n");
		}
	}

	close(fd);
	printf("apptest: %s closed\n", devname);
	fflush(stdout);

	return 0;
}
