/***************************************
 * 向某队列读取一个消息
 * gcc mqreceive.c -o mqreceive -lrt
 * ./mqreceive <mq-name>
 ***************************************/
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <unistd.h>          /* getopt */
#include <stdio.h>
#include <stdlib.h>

#define errExit(msg)	do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

int main(int argc, char **argv)
{
	int c, flags;

	mqd_t mqd;

	ssize_t n;

	size_t prio;  // 优先级

	void *buff;   // 缓冲区大小

	struct mq_attr attr;

	flags = O_RDONLY;

	// 命令行选项 -n 指定非阻塞属性，当队列没有消息，返回错误
	while ((c = getopt(argc, argv, "n")) != -1) {
		switch (c) {
			case 'n':
				flags |= O_NONBLOCK;
				break;
		}
	}

	if (optind != argc - 1) {
		errExit("usage: mqreceive [-n] <name>");
	}

	mqd = mq_open(argv[optind], flags);

	mq_getattr(mqd, & attr);

	buff = malloc(attr.mq_msgsize);

	n = mq_receive(mqd, buff, attr.mq_msgsize, &prio);

	if (n == -1) {
		errExit("message queue");
	}

	printf("read %ld bytes, priority = %u\n", (long)n, prio);

	exit(EXIT_SUCCESS);
}
