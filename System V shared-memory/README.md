## System V 共享内存

先调用 shmget，再调用 shmat。

### System V 共享内存 API

> 创建一个新的共享内存区

```c
#include <sys/ipc.h>
#include <sys/shm.h>

int shmget(key_t key, size_t size, int shmflg);
```

> 打开的共享内存区后，将其附接到调用进程的地址空间

```c
#include <sys/types.h>
#include <sys/shm.h>

void *shmat(int shmid, const void *shmaddr, int shmflg);
```

> 主动断接内存区

```c
#include <sys/types.h>
#include <sys/shm.h>

int shmdt(const void *shmaddr);
```

> 对一个共享内存区的多种操作

```c
#include <sys/ipc.h>
#include <sys/shm.h>

int shmctl(int shmid, int cmd, struct shmid_ds *buf);

三个命令：
IPC_RMID：删除 
IPC_SET：设置 
IPC_STAT：获取
```

### 共享内存限制

系统默认的内容，可通过下述命令查看：

```shell
cat /proc/sys/kernel/shmmax //共享内存区最大字节数
cat /proc/sys/kernel/shmall //最多共享内存区数
cat /proc/sys/kernel/shmmni //最大共享内存区标识符数
```
