#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 4096

// tcp server

int main(int argc, char* argv[])
{
	int listenfd, connfd;

	struct sockaddr_in servaddr;

	char buff[4096];

	int n;
	
	// 创建 socket，socket 描述符对应一个客户端，流
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("create socket error : %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;     // IPV4
	servaddr.sin_port = htons(8888);  // 端口
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 任意地址，IP地址转换函数

	// 绑定，IP地址+端口+协议簇
	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
	{
		printf("bind socket error : %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}
	
	// 监听，backlog 为连接队列大小
	if (listen(listenfd, 5) == -1)
	{
		printf("listen socket error : %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}

	printf("*****waiting for the client's request*****\n");

	// 持续接包
	while (1)
	{
		// accept 返回是已连接描述字
		if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1)
		{
			printf("accept socket error : %s(errno: %d)", strerror(errno), errno);
			continue;
		}
		
		// 接收客户端发过来的包
		n = recv(connfd, buff, MAXLINE, 0);
		buff[n] = '\0';

		printf("recv msg from client: %s\n", buff);
		
		// 收到包，就关闭
		close(connfd);
	}

	// 服务端 socket 描述符
	close(listenfd);
	
	return 0;
}
