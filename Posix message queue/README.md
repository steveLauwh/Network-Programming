## Posix IPC 之消息队列

消息队列可认为是一个消息链表。每个消息都是一个记录，它是由发送者赋予一个优先级。

### Posix 消息队列的特性

* 对 Posix 消息队列进行读操作总是返回最高优先级的最早消息。
* 当往一个空队列放置一个消息时，Posix 消息队列允许产生一个信号或启动一个线程。
* 队列中的每个消息包含一个无符号整数优先级、消息的数据部分的长度、数据本身。
* 某进程往一个消息队列中写入消息前，并不需要另外某个进程在该队列上等待消息的到达。
* 管道和FIFO是随着进程的持续性，而消息队列是随着内核的持续性。

### Posix 消息队列的 API

> 打开和关闭消息队列

```c
#include <mqueue.h>

/* 打开消息队列，成功返回值为消息队列描述符 */
mqd_t mq_open(const char *name, int oflag, /* mode_t mode, struct mq_attr *attr */);

/* 关闭消息队列，但消息队列并不从系统中删除 */
mqd_t mq_close(mqd_t mqdes);

/* 从系统中删除一个消息队列 */
mqd_t mq_unlink(const char *name);
```

> 消息队列的属性

```c
#include <mqueue.h>

struct mq_attr {
    long mq_flags;    // 消息队列的标志：0 或 O_NONBLOCK, 用来表示是否阻塞   
    long mq_maxmsg;   // 消息队列的最大消息数  
    long mq_msgsize;  // 消息队列中每个消息的最大字节数  
    long mq_curmsgs;  // 消息队列中当前的消息数目  
};

/* 获取当前消息队列的属性 */
mqd_t mq_getattr(mqd_t mqdes, struct mq_attr *attr);

/* 设置当前消息队列的属性 */
mqd_t mq_setattr(mqd_t mqdes, const struct mq_attr *newattr, struct mq_attr *oldattr);
```

mq_setattr 可以设置的属性只有 mq_flags，用来设置或清除消息队列的非阻塞标志。每个队列的最大消息数 mq_maxmsg 和每个消息的字节数 mq_msgsize 只能在创建队列(mq_open)时设置。队列中的当前消息数目 mq_curmsgs 只能获取。
