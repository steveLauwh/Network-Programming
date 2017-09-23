## 多线程的API

一个进程内的所有线程共享同一个全局内存空间。这使得线程间很容易共享信息，但是这种容易性也带来了同步问题。

> 线程的创建

pthread_create 用于创建新的线程，可以给线程传入一个 void * 类型的参数，例如一个结构体指针或者一个数值。

系统并不能保证哪个线程会先运行：新创建的线程还是调用线程。

```c
#include <pthread.h>

int pthread_create(pthread_t *thread, const pthread_attr_r *attr, void *(*start_routine) (void*), void *arg);
```

> 等待给定线程终止

```c
#include <pthread.h>

int pthread_join(pthread_t tid, void **retval);
```

> 线程退出

```c
#include <pthread.h>

void pthread_exit(void *retval);
```

> 获取自己的线程ID

```c
#include <pthread.h>

pthread_t pthread_self(void);
```

> 将指定的线程变为 detached

```c
#include <pthread.h>

int pthread_detach(pthread_t tid);
```
