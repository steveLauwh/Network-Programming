## 互斥锁和条件变量

互斥锁和条件变量是同步的基本组成部分。

互斥锁和条件变量出自 Posix.1 线程标准。

### 互斥锁：上锁与解锁

互斥锁是指相互排斥，最基本的同步形式；用于保护临界区，以保证任何时刻只有一个线程或进程在执行其中的代码。

互斥锁通常用于保护由多个线程或多个进程分享的共享数据。

保护一个临界区：
```c
lock_the_mutex(...);
临界区
unlock_the_mutex(...);
```

互斥锁上锁和解锁：
```c
#include <pthread.h>

int pthread_mutex_lock(pthread_mutex_t *mptr);
int pthread_mutex_trylock(pthread_mutex_t *mptr);
int pthread_mutex_unlock(pthread_mutex_t *mptr);
```

当期待的条目尚未准备好，需要一次次地循环，每次给互斥锁解锁又上锁。这称为轮询，是一种对 CPU 时间的浪费。

### 条件变量

互斥锁用于上锁，条件变量则用于等待。

### 有了互斥锁，为什么需要条件变量
