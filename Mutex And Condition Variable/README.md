# 互斥锁和条件变量

互斥锁和条件变量是同步的基本组成部分。

互斥锁和条件变量出自 Posix.1 线程标准。

## 互斥锁：上锁与解锁

互斥锁是指相互排斥，最基本的同步形式；用于保护临界区，以保证任何时刻只有一个线程或进程在执行其中的代码。

互斥锁通常用于保护由多个线程或多个进程分享的共享数据。

**保护一个临界区：**
```c
lock_the_mutex(...);
临界区
unlock_the_mutex(...);
```

**互斥锁的创建**

```c
#include <pthread.h>

// 静态初始化
pthread_mutex_t fastmutex = PTHREAD_MUTEX_INITIALIZER;

// 动态初始化
int  pthread_mutex_init(pthread_mutex_t  *mutex,  const  pthread_mutex_attr_t *mutexattr);
```

**互斥锁销毁**

```c
#include <pthread.h>

int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

**互斥锁上锁和解锁：**
```c
#include <pthread.h>

int pthread_mutex_lock(pthread_mutex_t *mptr);

// 锁已经被占有时返回 EBUSY，而不是挂起等待
int pthread_mutex_trylock(pthread_mutex_t *mptr);

int pthread_mutex_unlock(pthread_mutex_t *mptr);
```

当期待的条目尚未准备好，需要一次次地循环，每次给互斥锁解锁又上锁。这称为轮询，是一种对 CPU 时间的浪费。

## 条件变量

互斥锁用于上锁，条件变量则用于等待。

条件变量是类型为 pthread_cond_t 的变量。

**条件变量的创建**

```c
#include <pthread.h>

// 静态
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// 动态
int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr);
```

**条件变量的销毁**

```c
#include <pthread.h>

int pthread_cond_destroy(pthread_cond_t *cond);
```

**条件变量：等待与信号发送**

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

**pthread_cond_signal 写在互斥锁操作之间，还是之后？**

放在互斥锁操作之间：

```c
pthread_mutex_lock
    xxxxxxx
pthread_cond_signal
pthread_mutex_unlock
```

缺点：

在某下线程的实现中，会造成等待线程从内核中唤醒（由于cond_signal)然后又回到内核空间（因为cond_wait返回后会有原子加锁的行为），
所以一来一回会有性能的问题。但是在 Linux Threads 或者 NPTL 里面，就不会有这个问题，因为在Linux 线程中，有两个队列，
分别是 cond_wait 队列和 mutex_lock 队列， cond_signal 只是让线程从 cond_wait 队列移到 mutex_lock 队列，
而不用返回到用户空间，不会有性能的损耗。所以在 Linux 中推荐使用这种模式。

放在互斥锁操作之后：

```c
pthread_mutex_lock
    xxxxxxx
pthread_mutex_unlock
pthread_cond_signal
```

优点：不会出现之前说的那个潜在的性能损耗，因为在 signal 之前就已经释放锁了

缺点：如果 unlock 和 signal 之前，有个低优先级的线程正在 mutex 上等待的话，
那么这个低优先级的线程就会抢占高优先级的线程（cond_wait的线程)，而这在上面的放中间的模式下是不会出现的。

### 有了互斥锁，为什么需要条件变量？

互斥锁一个明显的缺点是只有两种状态：锁定和非锁定。互斥锁不能跨线程，条件变量可以限定两个线程之间进行可靠地同步。

条件变量通过允许线程阻塞和等待另一个线程发送信号的方法弥补了互斥锁的不足，它常和互斥锁一起使用。

条件变量也是一种互斥的资源，需要互斥锁保护条件变量，防止竞争。

pthread_cond_wait(&cond, &mutex); // 相当于 unlock(MUTEX), wait(COND), lock(MUTEX) 三个操作

### pthread_cond_wait() 前要加一个 while 循环来判断条件是否为假的原因？

在多核处理器下，pthread_cond_signal() 可能会激活多于一个线程（阻塞在条件变量上的线程）。 

当一个线程调用 pthread_cond_signal() 后，多个调用 pthread_cond_wait() 或 pthread_cond_timedwait() 的线程返回。
这种效应成为”虚假唤醒”(spurious wakeup) 。

pthread_cond_wait() 中的 while 循环不仅仅在等待条件变量前检查条件变量，实际上在等待条件变量后也检查条件变量。

这样对 condition 进行多做一次判断，即可避免“虚假唤醒”。

