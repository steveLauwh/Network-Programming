## 记录上锁(同一文件某部分区域)

记录上锁是读写锁的一种扩展类型，它可用于有亲缘关系或无亲缘关系的进程之间共享某个文件的读与写。
用于不同进程间的上锁，而不是用于同一进程内不同线程间的上锁。

被锁住的文件通过其描述符访问，指向上锁操作的函数是 fcntl。

记录锁的功能：当一个进程正在读或修改文件的某个部分时，它可以阻止其他进程修改同一文件区。

## 文件锁

对文件而言。

按功能分：

* 共享读锁：文件描述符必须读打开，一个进程上了读锁，其它进程也可以上读锁进行读取
* 独占写锁：文件描述符必须写打开，一个进程上了写锁，其它进程就不能上写锁或读锁进行写操作

按类型分：

* 建议锁：要求上锁文件的进程都要检测是否有锁的存在，并尊重已有的锁，Linux 默认的锁类型
* 强制锁：由内核和系统执行的锁

### Posix fcntl 记录上锁 API

记录上锁的 Posix 接口是 fcntl 函数。

```c
#include <fcntl.h>

int fcntl(int fd, int cmd, .../*struct flock *arg*/);

// flock 结构的指针
strcut flock {
    short  l_type; //F_RDLCK, F_WRLCK, F_UNLCK
    short l_whence; //SEEK_SET, SEEK_CUR, SEEK_END
    off_t   l_start;
    off_t   l_len;
    pid_t  l_pid; //PID returned by F_GETLK
}

// 用于记录上锁的 cmd 参数共有三个值
F_SETLK：获取（l_type 成员为 F_RDLCK 或 F_WRLCK）或释放（l_type 为 F_UNLCK）由 arg 指向的 flock 结构所描述的锁。

F_SETLCW：该命令与上一个命令类似，不过如果无法将所请求的锁授予调用进程，调用进程将阻塞到该锁能够分配为止。

F_GETLK：检查由arg指向的锁以确定是否有某个已存在的锁会妨碍将新锁授予调用进程。
```

fcntl 记录上锁既可以用于读也可以用于写，对于一个文件的任意字节，最多只能存在一种类型的锁。而且一个给定字节可以有多个读出锁，一个写入锁。
