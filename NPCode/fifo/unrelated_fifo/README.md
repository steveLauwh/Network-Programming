## 利用两个 FIFO 进行客户端-服务端通信(没有亲缘关系)

编译：make

servermain.c -- 服务端主函数

clientmain.c -- 客户端主函数

为运行这对客户端和服务器，先在后台启动服务器：

./servermain &

然后另起一个终端，执行客户端的可执行文件 ./clientmain
