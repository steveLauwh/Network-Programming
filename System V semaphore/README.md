## System V 信号量

System V 信号量相对于 POSIX 信号量最大的区别是在信号量的操作复杂度。

计数信号量集：一个或多个信号量，其中每个都是计数信号量。

对于信号量集中的信号量数目系统内核是存在限制的，由内核参数：SEMMSL决定。

### System V 信号量 API

> System V 信号量的创建和打开

```c
#include <sys/sem.h>  

int semget(key_t key, int nsems, int semflg);  // 若成功就返回为非负的标识符，否则返回-1  
```

> System V 信号量的操作

```c
#include <sys/sem.h>  

int semop(int semid, struct sembuf *sops, unsigned nsops); 

// 成功返回 0，出错返回 -1  
int semtimedop(int semid, struct sembuf *sops, unsigned nsops, struct timespec *timeout);  
```

> System V 信号量的控制

```c
#include <sys/sem.h>  

// 若失败返回 -1，并设置 errno
int semctl(int semid, int semnum, int cmd, .../* union semun arg*/);
```

### System V 信号量的销毁

通过 semctl 传入 IPC_RMID 对该信号量集进行删除时，会立即将该信号量从系统中彻底删除，不能再对该信号量进行任何访问。
