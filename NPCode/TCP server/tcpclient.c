#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#define MAXLINE 4096

// tcp client

int main(int argc, char* argv[])
{
	int sockfd, n;
	char buf[4096];
	struct sockaddr_in servaddr;

	if (argc != 2)
	{
		printf("usage: ./tcpclient <ipaddress>\n");
		return 0;
	}
	
	// 创建客户端 socket，TCP
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8888);
	
	// IP地址转换
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
		printf("inet_pton error for %s\n", argv[1]);
		return 0;
	}

	// 发起 connect，连接服务器
	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{	
		printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}

	printf("send msg to server: \n");
	
	// 终端输入
	fgets(buf, 4096, stdin);

	// 发送
	if (send(sockfd, buf, strlen(buf), 0) < 0)
	{
		printf("send error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;	
	}

	// 关闭
	close(sockfd);

	return 0;
}
