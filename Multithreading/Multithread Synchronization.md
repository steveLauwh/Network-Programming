## 多线程的同步

一个进程下可以有多个线程，它们共享资源。多线程相当于一个并发系统，一般同时执行多个任务。
如果多个任务可以共享资源，特别是同时写入某个变量的时候，就需要解决同步的问题。

对于多线程程序来说，同步(synchronization)是指在一定的时间内只允许某一个线程访问某个资源 。
而在此时间内，不允许其它的线程访问该资源。

可以通过互斥锁(mutex)，条件变量(condition variable)，读写锁(reader-writer lock)和信号量(POSIX semphore)来同步资源。

* [互斥锁](https://github.com/steveLauwh/Network-Programming/tree/master/Mutex%20And%20Condition%20Variable)：lock 和 unlock
两个状态，互斥锁一般设置成全局变量。提供一个可以在同一时间，只让一个线程访问临界资源的的操作接口。

* [条件变量](https://github.com/steveLauwh/Network-Programming/edit/master/Mutex%20And%20Condition%20Variable)：特别适用于多个线程
等待某个条件的发生。用于多线程之间关于共享数据状态变化的通信。当一个动作需要另外一个动作完成时才能进行。

* [读写锁](https://github.com/steveLauwh/Network-Programming/tree/master/Read-Write%20Lock)：多个线程可以读操作，只能一个线程写操作。特别适用
于对数据结构的读操作次数多于写操作次数的场合。

* [Posix 信号量](https://github.com/steveLauwh/Network-Programming/tree/master/Posix%20semaphore)：允许多个线程同时进入临界区。

## 多线程重入

可重入函数：可以由多于一个任务并发使用，而不必担心数据错误的函数。

不可重入函数：只能由一个任务所占用，除非能保证函数的互斥。

### 线程安全与可重入函数的区别

* 可重入函数是线程安全函数的一种，其特点在于它们被多个线程调用时，不会引用任何共享数据。
* 线程安全是在多个线程情况下引发的，而可重入函数可以在只有一个线程的情况下来说。
* 线程安全不一定是可重入的，而可重入函数则一定是线程安全的。
* 如果一个函数中有全局变量，那么这个函数既不是线程安全也不是可重入的。
* 如果将对临界资源的访问加上锁，则这个函数是线程安全的，但如果这个可重入函数若锁还未释放则会产生死锁，因此是不可重入的。
* 线程安全函数能够使不同的线程访问同一块地址空间，而可重入函数要求不同的执行流对数据的操作互不影响使结果是相同的。

## 参考

* [Linux多线程与同步](http://www.cnblogs.com/vamei/archive/2012/10/09/2715393.html)
* [使用可重入函数进行更安全的信号处理](https://www.ibm.com/developerworks/cn/linux/l-reent.html)
* [线程安全与可重入函数之间的区别](http://m.blog.csdn.net/WX_East/article/details/74002268)
* [可重入性与线程安全](http://www.cnblogs.com/zhaoyl/archive/2012/10/03/2711018.html)
