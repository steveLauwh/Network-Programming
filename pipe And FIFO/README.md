## 消息传递之管道(pipe)

管道是无名管道，由 pipe 函数创建。

![](https://github.com/steveLauwh/Network-Programming/raw/master/image/SigProcPipe.PNG)

> 函数原型：

```c
#incude <unistd.h>

int pipe(int pipefd[2]);
```

返回值：若成功则返回 0，若出错则返回 -1。

参数说明：pipefd[0] 表示管道读端，pipefd[1] 表示管道写端。

> 管道的作用

创建无名管道，实现父子进程间通信。

> 管道的流程(实现单向数据流)

1. 创建无名管道
2. 创建子进程，由父进程通过 fork 创建
3. 在父进程进行写操作，子进程进行读操作。

![](https://github.com/steveLauwh/Network-Programming/raw/master/image/SigProcPipeFork.PNG)

![](https://github.com/steveLauwh/Network-Programming/raw/master/image/TwoProcPipe.PNG)

如果实现双向数据流，需要使用两个管道操作，所以全双工管道的真正实现是由两个半双工管道构成的。

![](https://github.com/steveLauwh/Network-Programming/raw/master/image/MultiProcPipe.PNG)

## 消息传递之 FIFO

无名管道的特点是只能用于有一个共同祖先进程的各个进程之间。

FIFO 是有名管道，由 mkfifo 函数创建。

因为每个 FIFO 有一个路径名与之关联，从而允许无亲缘关系的进程访问同一个 FIFO。

> 函数原型

```c
#include <sys/types.h>
#include <sys/stat.h>

int mkfifo(const char *pathname, mode_t mode);
```

返回值：若成功则返回 0，若出错则返回 -1。

参数说明：pathname 为fifo 文件的路径名，mode 为 fifo 文件的访问权限。

> FIFO 的作用

可以使无亲缘关系的两个进程进行通信。

> FIFO 的流程

写管道：

1. 创建 FIFO 文件
2. 使用 open 函数打开 FIFO 文件
3. 写数据到 FIFO

读管道：

1. 使用 open 函数打开 FIFO 文件 
2. 从 FIFO 中读出
3. 显示数据
4. 关闭 FIFO 文件

> 删除 FIFO

```c
#include <unistd.h>

int unlink(const char *pathname);
```

FIFO 的名字只有通过调用 unlink 才从文件系统中删除。

## 管道 pipe 与 FIFO 区别

* 创建并打开一个管道只需调用 pipe。创建并打开一个 FIFO 则需在调用 mkfifo 后再调用 open
* 管道在所有进程最终都关闭它之后自动消失。FIFO 的名字则只有通过调用 unlink 才从文件系统中删除
* pipe 适用于有亲缘关系的进程间通信，FIFO 可以无亲缘关系的进程间通信

