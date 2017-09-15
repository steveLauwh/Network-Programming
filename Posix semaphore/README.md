## Posix 信号量

信号量(semaphore) 是一种用于提供不同进程间或一个给定进程的不同线程间同步手段的原语。

三种类型的信号量：

* Posix 信号量：使用 Posix IPC 名字标识。 （有名信号量）
* Posix 基于内存的信号量：存放在共享内存区中。 （无名信号量）
* System V 信号量：在内核中维护。

### Posix 信号量的操作

> 创建一个信号量

需要初始化信号量

> 等待一个信号量 wait(P 操作)

如果信号量的值小于或等于 0，那就等待(阻塞)。

如果信号量的值大于 0，就减 1

> 挂出一个信号量 post(V 操作)

将信号量的值加 1

### 信号量、互斥锁和条件变量之间的差异

* 互斥锁必须总是由给它上锁的线程解锁，信号量的挂出却不必由执行过它的等待操作的同一线程执行
* 互斥锁要么被锁住，要么被解开
* 信号量的挂出操作总是被记住，因为信号量有一个计数值，挂出操作总会将该计数值加1，然而当向条件变量发送一个信号时，如果没有线程等待在条件变量，那么该信号会丢失。

### Posix 信号量 API

**Posix 有名信号量**

> 创建一个有名信号量或打开一个已存在的有名信号量

```c
#include <semaphore.h>  

//成功返回信号量指针，失败返回SEM_FAILED  
sem_t *sem_open(const char *name, int oflag);  

sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);  
```

> 关闭一个信号量

```c
#include <semaphore.h>  

//成功返回0，失败返回-1  
int sem_close(sem_t *sem);  
```

> 将有名信号量从系统中删除

```c
#include <semaphore.h>  

//成功返回0，失败返回-1  
int sem_unlink(const char *name);  
```

> 信号量的 P 操作

```c
#include <semaphore.h>  

//成功返回0，失败返回-1   
int sem_wait(sem_t *sem);  
    
int sem_trywait (sem_t *sem);                              
```

sem_trywait 和 sem_wait 的差别是，当信号量的值等于 0 的，调用线程不会阻塞，直接返回，并标识 EAGAIN 错误。

> 信号量的 V 操作

```c
#include <semaphore.h>  
  
int sem_post(sem_t *sem);  //成功返回0，失败返回-1 
```

> 获取当前信号量的值

```c
#include <semaphore.h>  
  
int sem_getvalue(sem_t *sem,  int *sval);  //成功返回0，失败返回-1  
```

该函数返回当前信号量的值，通过sval输出参数返回，如果当前信号量已经上锁（即同步对象不可用），那么返回值为0，或为负数，其绝对值就是等待该信号量解锁的线程数。

**Posix 无名信号量的创建和销毁**

```c
#include <semaphore.h>  
  
int sem_init(sem_t *sem, int pshared, unsigned int value);  //若出错则返回-1  

int sem_destroy(sem_t *sem);  //成功返回0，失败返回-1  
```

sem_init() 用于无名信号量的初始化。无名信号量在初始化前一定要在内存中分配一个 sem_t 信号量类型的对象，这就是无名信号量又称为基于内存的信号量的原因。

### 信号量的经典问题——生产者和消费者

### Posix 信号量的三种实现

* 使用 FIFO 实现
* 使用内存映射 I/O 实现
* 使用 System V 信号量实现
