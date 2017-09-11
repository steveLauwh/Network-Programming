## System V 之消息队列

### System V 消息队列与 Posix 消息队列的区别

* 对 System V 消息队列进行读操作，返回任意指定优先级的消息；而 Posix 消息队列是返回最高优先级的最早消息
* 当往一个空队列放置一个消息时，Posix 消息队列允许产生一个信号或启动一个线程，System V 消息队列不提供类似机制
* System V 消息队列使用消息队列标识符标识。具有足够特权的任何进程都可以往一个给定队列放置一个消息，具有足够特权的任何进程都可以从一个给定队列读出一个消息。

### System V 消息队列 API

> msgget 函数

```c
#include <sys/msg.h>

/* 创建一个新的消息队列或访问一个已存在的消息队列，返回值是一个整数标识符 */
int msgget(key_t key, int msgflag);
```

> msgsnd 函数

```c
#include <sys/msg.h>

/* 往消息队列中放入一个消息 */
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflag);
```

> msgrcv 函数

```c
#include <sys/msg.h>

/* 从消息队列中读出一个消息，返回所接收消息中数据的字节数 */
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
```

> msgctl 函数

```c
#include <sys/msg.h>

/* 在一个消息队列上的各种控制操作 */
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```


