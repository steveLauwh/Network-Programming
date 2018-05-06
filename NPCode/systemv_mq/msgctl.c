#include <sys/msg.h>

#define MSG_R 0400
#define MSG_W 0200
#define SVMSG_MODE (MSG_R | MSG_W | MSG_R >> 3 | MSG_R >> 6)

struct msgbuf {
    long mtype;
    char mtext[1];
};

int main()
{
    int msqid;
    
	// System V message queue
    struct msqid_ds info;
    struct msgbuf buf;

	// 创建一个新的消息队列
    msqid = msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);

    buf.mtype = 1;
    buf.mtext[0] = 1;

	// 放置一个消息，消息长度为 1 字节
	msgsnd(msqid, &buf, 1, 0);

	// 给调用者返回与所指定消息队列对应的当前 msqid_ds 结构
	msgctl(msqid, IPC_STAT, &info);

	printf("read-write: %03o, cbytes = %lu, qnum = %lu, qbytes = %lu\n",
		   info.msg_perm.mode & 0777, (unsigned long)info.msg_cbytes,
		   (unsigned long)info.msg_qnum, (unsigned long)info.msg_qbytes);

	system("ipcs -q");

	// 从系统中删除由 msqid 指定的消息队列
	msgctl(msqid, IPC_RMID, NULL);

	return 0;
}
