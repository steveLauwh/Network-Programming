#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <unistd.h>

#define errExit(msg)	do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s mq-name \n", argv[0]);
		exit(EXIT_FAILURE);
	}
  // 从系统中删除一个消息队列
	if (mq_unlink(argv[1]) == -1) {
		errExit("mqunlink error");
	}

	exit(EXIT_SUCCESS);
}
