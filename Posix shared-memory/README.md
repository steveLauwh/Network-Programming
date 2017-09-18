## 共享内存

共享内存是可用 IPC 形式中最快的。一旦这样的内存区映射到共享它的进程的地址空间，这些进程间数据的传递就不再涉及到内核。

使用(管道、FIFO、消息队列)，两个进程要交换信息时，必须经过由内核传递。

共享内存就是允许两个不相关的进程访问同一个逻辑内存。

共享内存并未提供同步机制，需要借助同步机制，如信号量，来同步对共享内存的访问。

> mmap

mmap 函数把一个文件或一个 Posix 共享内存区对象映射到调用进程的地址空间。

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

### 参考

* [认真分析mmap：是什么 为什么 怎么用](http://www.cnblogs.com/huxiao-tee/p/4660352.html)
