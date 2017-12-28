#include <sys/types.h>
#include <sys/stat.h>  // mkfifo, mode_t 
#include <errno.h>     // errno
#include <stdlib.h>    // EXIT_SUCESS
#include <fcntl.h>     // O_RDONLY
#include "client.h"
#include "server.h"

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"

// 文件权限标志：用户可读，用户可写，组成员可读，其它可读
#define FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

#define ERR_EXIT(x) \
	do {		\
		perror(x); \
		exit(EXIT_FAILURE); \
	} while(0)

/***
 * 使用两个 FIFO 进行客户端与服务端通信，这里是父子进程
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
	
	// 2. 子进程，作为服务端，先读后写
	if ((childfd = fork()) == 0) {
		readfd = open(FIFO1, O_RDONLY, 0);  
		writefd = open(FIFO2, O_WRONLY, 0);

		server(readfd, writefd);

		exit(EXIT_SUCCESS);
	}

	// 2. 调用 open，父进程，作为客户端，注意必须先写后读，否则会造成死锁
	if ((writefd = open(FIFO1, O_WRONLY, 0)) < 0) {
		ERR_EXIT("open FIFO1");
	}

	if ((readfd = open(FIFO2, O_RDONLY, 0)) < 0) {
		ERR_EXIT("open FIFO2");
	}

	client(readfd, writefd);

	if ((waitpid(childfd, NULL, 0)) == -1) {
		ERR_EXIT("waitfd");
	}

	close(readfd);

	close(writefd);

	unlink(FIFO1); // 使用 unlink 将 FIFO 名字从文件系统中删除
	
	unlink(FIFO2);

	exit(EXIT_SUCCESS);
}

