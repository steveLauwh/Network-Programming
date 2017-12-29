#include "client.h"
#include "fifo.h"

#define ERR_EXIT(x) \
	do {		\
		perror(x); \
		exit(EXIT_FAILURE); \
	} while(0)

// 客户端侧
int main(int argc, char *argv[])
{
	int readfd, writefd;

	// 调用 open，作为客户端，注意必须先写后读，否则会造成死锁
	if ((writefd = open(FIFO1, O_WRONLY, 0)) < 0) {
		ERR_EXIT("open FIFO1");
	}

	if ((readfd = open(FIFO2, O_RDONLY, 0)) < 0) {
		ERR_EXIT("open FIFO2");
	}

	client(readfd, writefd);

	close(readfd);

	close(writefd);

	unlink(FIFO1); // 使用 unlink 将 FIFO 名字从文件系统中删除
	
	unlink(FIFO2);

	exit(EXIT_SUCCESS);
}

