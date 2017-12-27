#include "client.h"
#include <stdio.h>
#include <stdlib.h>   
#include <unistd.h>   // read, write

#define MAXLINE 4096

void client(int readfd, int writefd)
{
	ssize_t n;

	size_t len;

	char buf[MAXLINE];

	printf("Please input: \n");

	fgets(buf, MAXLINE, stdin);

	len = sizeof(buf);

	if (buf[len-1] == '\n') {
		len--;
	}

	// 写入到管道1
	if (write(writefd, buf, len) == -1) {
		perror("write");
		exit(EXIT_FAILURE);
	}

	// 从管道2读出
	while ((n = read(readfd, buf, MAXLINE)) > 0) {
		printf("Read the input: \n");
		write(STDOUT_FILENO, buf, n);
	}
}
