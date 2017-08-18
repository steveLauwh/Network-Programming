## Posix 与 System V

在阅读「Unix 网络编程-卷2：进程间通信」书籍，发现分为 Posix IPC 和 System V IPC 两种类型。它们是两个不同的标准；

Linux 系统编程支持 Posix(Portable Operating System Interface) 和 System V(System Five)) 两种标准。

### System V 特点

* 比较老
* 接口复杂

### Posix 特点

* 新标准
* 接口使用比较方便

POSIX IPC 已有效地替代了 System V IPC，但仍然保留了 System V IPC 以支持较早版本的应用程序。
