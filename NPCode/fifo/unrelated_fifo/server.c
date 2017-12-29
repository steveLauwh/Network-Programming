#include "server.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>  // O_RDONLY
#include <errno.h>  // errno
#include <string.h> // strerror

#define MAXLINE 4096

void server(int readfd, int writefd)
{
	int fd;
	ssize_t n;

	char buf[MAXLINE+1];
	
	// 从 FIFO1 读出
	if ((n = read(readfd, buf, MAXLINE)) < 0) {
		perror("server read");
		exit(EXIT_FAILURE);
	}
	buf[n] = '\0';

	if ((fd = open(buf, O_RDONLY)) < 0) {
		snprintf(buf + n, sizeof(buf) - n, ": can't open, %s\n", strerror(errno));
		n = strlen(buf);
		write(writefd, buf, n);
	} else {
		while ((n = read(fd, buf, MAXLINE)) > 0) {
			write(writefd, buf, n);  // 写入 FIFO2
		}

		close(fd);
	}
}

