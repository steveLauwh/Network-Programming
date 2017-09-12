## 读写锁(read-write lock)

### 什么是读写锁？

获取一个读写锁用于读称为共享锁，获取一个读写锁用于写称为独占锁。

读写锁：多个读出者和一个写入者。

读写锁的三种状态：

* 当读写锁是写加锁状态时，在这个锁被解锁之前，所有试图对这个锁加锁的线程都会被阻塞

* 当读写锁在读加锁状态时，所有试图以读模式对它进行加锁的线程都可以得到访问权，但是以写模式对它进行加锁的线程将会被阻塞

* 当读写锁在读模式的锁状态时，如果有另外的线程试图以写模式加锁，读写锁通常会阻塞随后的读模式锁的请求，
  这样可以避免读模式锁长期占用，而等待的写模式锁请求则长期阻塞。

### 读写锁的 API

> 读写锁初始化

```c
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;  // 静态分配初始化

#include <pthread.h>

// 动态初始化
int pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);

// 销毁读写锁
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
```

> 获取与释放读写锁

```c
#include <pthread.h>

// 获取一个读出锁
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);

// 获取一个写入锁
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);

// 释放一个读出锁或写入锁
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
```

### 总结

与普通的互斥相比，当被保护数据的读访问比写访问更为频繁时，读写锁能提供更高的并发度。


