## System V message queue

> System V 消息队列与 Posix 消息队列的区别

* 对 System V 消息队列进行读操作，返回任意指定优先级的消息；而 Posix 消息队列是返回最高优先级的最早消息
* 当往一个空队列放置一个消息时，Posix 消息队列允许产生一个信号或启动一个线程，System V 消息队列不提供类似机制

