/***************************************
 * 向某队列增加一个消息
 * gcc mqsend.c -o mqsend -lrt
 * ./mqsend <mq-name> <bytes> <priority>
 ***************************************/
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <unistd.h>          /* getopt */
#include <stdio.h>
#include <stdlib.h>

#define errExit(msg)	do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

#define FILE_MODE   S_IRUSR | S_IWUSR

// 如果使用 O_CREAT 时文件存在，就返回错误信息，它可以测试文件是否存在
#define FLAGS       O_CREAT | O_WRONLY                   

int main(int argc, char **argv)
{
	mqd_t mqd;
	void *ptr;
	size_t len;
	size_t prio;

	if (argc != 4) {
		fprintf(stderr, "usage: %s <mq-name> <bytes> <priority>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	len = atoi(argv[2]);
	prio = atoi(argv[3]);

	// 创建一个消息队列
	mqd = mq_open(argv[1], FLAGS, FILE_MODE, NULL);

	if (mqd == -1) {
		errExit("mq_open");
	}

	ptr = calloc(len, sizeof(char));

	if (ptr == NULL) {
		exit(EXIT_FAILURE);
	}

	// mq_send 向消息队列中发送消息
	if (mq_send(mqd, ptr, len, prio) == -1) {
		errExit("mq_send");
	} else {
		printf("message queue send ok\n");
	}

	exit(EXIT_SUCCESS);
}
