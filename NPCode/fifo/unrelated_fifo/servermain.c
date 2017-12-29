#include "fifo.h"
#include "server.h"

// 文件权限标志：用户可读，用户可写，组成员可读，其它可读
#define FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

#define ERR_EXIT(x) \
	do {		\
		perror(x); \
		exit(EXIT_FAILURE); \
	} while(0)

/***
 * 使用两个 FIFO 进行客户端与服务端通信，无亲缘关系的进程
 */
int main(int argc, char *argv[])
{
	int readfd, writefd;

	pid_t childfd;

	// 1. 使用 mkfifo 创建两个 FIFO
	if (mkfifo(FIFO1, FILE_MODE) < 0 && (errno != EEXIST)) {
		ERR_EXIT("FIFO1");		
	}

	if (mkfifo(FIFO2, FILE_MODE) < 0 && (errno != EEXIST)) {
		unlink(FIFO1);
		ERR_EXIT("FIFO2");
	}
	
	// 2. server 侧
	readfd = open(FIFO1, O_RDONLY, 0);  
	writefd = open(FIFO2, O_WRONLY, 0);

	server(readfd, writefd);

	exit(EXIT_SUCCESS);
}

