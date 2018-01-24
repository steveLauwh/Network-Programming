/********************************************
 * 创建一个消息队列
 * gcc mqcreate.c -o mqcreate -lrt
 * ./mqcreate /mq.1234
 *******************************************/
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
#define FLAGS       O_CREAT | O_EXCL                   

int main(int argc, char **argv)
{
	mqd_t mqd;
	struct mq_attr attr;

	if (argc != 2) {
		fprintf(stderr, "usage: %s mq-name \n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// 创建一个消息队列
	mqd = mq_open(argv[1], FLAGS, FILE_MODE, NULL);

	if (mqd == -1) {
		errExit("mq_open");
	} else {
		printf("create message queue");
	}

	if (mq_getattr(mqd, &attr) == -1) {
		errExit("mq_getattr");
	}

	printf("message number : %ld\n", attr.mq_maxmsg); // 消息队列的最大消息数
	printf("message size : %ld\n", attr.mq_msgsize);  // 消息队列的每个消息的最大大小
	printf("current message number : %ld\n", attr.mq_curmsgs);

	mq_close(mqd);  // 关闭消息队列，但消息队列不会从系统中删除

	if (mq_unlink(argv[1]) == 0) {
		printf("Delete mq from System!");
	} else {
		errExit("mq_unlink");
	}

	exit(EXIT_SUCCESS);
}
