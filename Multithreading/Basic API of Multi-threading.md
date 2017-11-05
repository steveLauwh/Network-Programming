## 多线程的API

一个进程内的所有线程共享同一个全局内存空间。这使得线程间很容易共享信息，但是这种容易性也带来了同步问题。

多线程就是允许一个进程内存在多个控制权，以便让多个函数同时处于激活状态，从而让多个函数的操作同时运行。

> **线程的创建**

pthread_create 用于创建新的线程，可以给线程传入一个 void * 类型的参数，例如一个结构体指针或者一个数值。

系统并不能保证哪个线程会先运行：新创建的线程还是调用线程。

```c
#include <pthread.h>

// 若线程创建成功，则返回 0
int pthread_create(pthread_t *thread, const pthread_attr_r *attr, void *(*start_routine) (void*), void *arg);
```

> **等待给定线程终止**

```c
#include <pthread.h>

// 线程阻塞的函数
int pthread_join(pthread_t tid, void **retval);
```

> **线程退出**

```c
#include <pthread.h>

void pthread_exit(void *retval);
```

> **获取自己的线程ID**

```c
#include <pthread.h>

pthread_t pthread_self(void);
```

> **将指定的线程变为 detached**

```c
#include <pthread.h>

int pthread_detach(pthread_t tid);
```

> **线程取消**

```c
#include <pthread.h>

int pthread_cancel(pthread_t thread);
```

> **线程的属性初始化和去除初始化**

```c
#include <pthread.h>

int pthread_attr_init(pthread_attr_t *attr);

int pthread_attr_destroy(pthread_attr_t *attr);
```

> **线程的属性**

```c
typedef struct
{
    int                          detachstate;     // 线程的分离状态
    int                          schedpolicy;     // 线程调度策略
    struct sched_param           schedparam;      // 线程的调度参数
    int                          inheritsched;    // 线程的继承性
    int                          scope;           // 线程的作用域
    size_t                       guardsize;       // 线程栈末尾的警戒缓冲区大小
    int                          stackaddr_set;   // 线程的栈设置
    void *                       stackaddr;       // 线程栈的位置
    size_t                       stacksize;       // 线程栈的大小
}pthread_attr_t;
```

分离线程没有被其他的线程所等待，自己运行结束了，线程也就终止了，马上释放系统资源。

## pthread_join 与 pthread_exit 的区别

* pthread_join 一般是主线程来调用，用来等待子线程退出，因为是等待，所以是阻塞的，一般主线程会依次添加所有它创建的子线程
* pthread_exit 一般是子线程调用，用来结束当前线程
* 子线程可以通过 pthread_exit 传递一个返回值，而主线程通过 pthread_join 获得该返回值，从而判断该子线程的退出是正常还是异常







