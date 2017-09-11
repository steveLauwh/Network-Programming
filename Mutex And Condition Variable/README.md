## 互斥锁和条件变量

互斥锁和条件变量是同步的基本组成部分。

互斥锁和条件变量出自 Posix.1 线程标准。

### 互斥锁：上锁与解锁

互斥锁是指相互排斥，最基本的同步形式；用于保护临界区，以保证任何时刻只有一个线程或进程在执行其中的代码。

互斥锁通常用于保护由多个线程或多个进程分享的共享数据。

**保护一个临界区：**
```c
lock_the_mutex(...);
临界区
unlock_the_mutex(...);
```

**互斥锁上锁和解锁：**
```c
#include <pthread.h>

int pthread_mutex_lock(pthread_mutex_t *mptr);
int pthread_mutex_trylock(pthread_mutex_t *mptr);
int pthread_mutex_unlock(pthread_mutex_t *mptr);
```

当期待的条目尚未准备好，需要一次次地循环，每次给互斥锁解锁又上锁。这称为轮询，是一种对 CPU 时间的浪费。

### 条件变量

互斥锁用于上锁，条件变量则用于等待。

条件变量是类型为 pthread_cond_t 的变量。

**条件变量：等待与信号发送：**

```c
#include <pthread.h>

/* 条件变量的等待 */
int pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr);

/* 条件变量的信号发送 */
int pthread_cond_signal(pthread_cond_t *cptr);
```

使用 pthread_cond_signal 只唤醒等待在相应条件变量上的一个线程。

**条件变量：定时等待和广播**

```c
#include <pthread.h>

/* 唤醒阻塞在相应条件变量上的所有线程 */
int pthread_cond_broadcast(pthread_cond_t *cptr);

/* 允许线程就阻塞时间设置一个限制值 */
int pthread_cond_timedwait(pthread_cond_t *cptr, pthread_mutex_t *mptr, const struct timespec *abstime);
```

### 有了互斥锁，为什么需要条件变量
