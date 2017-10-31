## 共享内存

共享内存是可用 IPC 形式中最快的。一旦这样的内存区映射到共享它的进程的地址空间，这些进程间数据的传递就不再涉及到内核。

使用(管道、FIFO、消息队列)，两个进程要交换信息时，必须经过由内核传递。

共享内存就是允许两个不相关的进程访问同一个逻辑内存。

共享内存并未提供同步机制，需要借助同步机制，如信号量，来同步对共享内存的访问。

`ipcs -m`：显示活动的共享内存信息。

`ipcrm -m SharedMemoryID`  // SharedMemoryID 为共享内存标识

## 共享内存的原理

两个不同进程 A、B 共享内存的意思是，同一块物理内存被映射到进程 A、B 各自的进程地址空间。进程 A 可以即时看到进程 B 对共享内存中数据的更新，反之亦然。

### Posix 共享内存 与 System V 共享内存的区别

Posix 共享内存区对象的大小可在任何时刻通过调用 ftruncate 修改，而System V 共享内存区对象的大小是在调用 shmget 创建时固定下来的。

### 内存映射文件

集中于 mmap 函数以及普通文件的内存映射，是对有亲缘关系的进程间共享内存空间的一种方法。

> mmap

mmap 函数把一个文件或一个 Posix 共享内存区对象映射到调用进程的地址空间。

open 函数打开，由 mmap 函数把得到的描述符映射到当前进程地址空间中的一个文件。

```c
// 进程在用户空间调用库函数 mmap
void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);
```

> munmap

```c
// 该调用在进程地址空间中解除一个映射关系
int munmap(void *addr, size_t len);
```

> msync

```c
// 可以通过调用 msync() 实现磁盘上文件内容与共享内存区的内容一致
int msync(void *addr, size_t len, int flags);
```

### Posix 共享内存

Posix 共享内存使用方法有以下两个步骤：
* 通过 shm_open 创建或打开一个 Posix 共享内存对象
* 然后调用 mmap 将它映射到当前进程的地址空间

> Posix 共享内存的创建（打开）和删除

```c
#include <sys/mman.h>  

// 成功返回非负的描述符，失败返回-1  
int shm_open(const char *name, int oflag, mode_t mode);  
                              
int shm_unlink(const char *name);  //成功返回0，失败返回-1                              
```

> 修改普通文件或共享内存区对象的大小

```c
#include <unistd.h>

int ftruncate(int fd, off_t length);
```

> 当打开一个已存在的共享内存区对象时，获取有关对象的信息

```c
#include <sys/types.h>
#include <sys/stat.h>

int fstat(int fd, struct stat *buf);
```

### 参考

* [认真分析mmap：是什么 为什么 怎么用](http://www.cnblogs.com/huxiao-tee/p/4660352.html)
