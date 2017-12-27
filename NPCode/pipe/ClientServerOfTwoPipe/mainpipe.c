#include <unistd.h>  // pipe, fork
#include <sys/wait.h>  // wait
#include <stdio.h>
#include <stdlib.h>  // exit, EXIT_FAILURE
#include "client.h"
#include "server.h"

/***
 * 使用两个管道方式进行客户端-服务端通信
 */

int main(int argc, char *argv[])
{
	int pipe1fd[2];
	int pipe2fd[2];

	pid_t childpid;

	/* 创建两个管道 */
	if (pipe(pipe1fd) == -1) {
		perror("pipe1");
		exit(EXIT_FAILURE);
	}

	if (pipe(pipe2fd) == -1) {
		perror("pipe2");
		exit(EXIT_FAILURE);
	}

	// 创建子进程
	childpid = fork();
	if (childpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	// 子进程作为 server
	if (childpid == 0) {
		close(pipe1fd[1]);
		close(pipe2fd[0]);
		
		// 子进程调用 server 函数
		server(pipe1fd[0], pipe2fd[1]);
		
		exit(EXIT_SUCCESS);
	} else { 
		// 父进程作为 client
		close(pipe1fd[0]);
		close(pipe2fd[1]);
		
		// 父进程调用 client 函数
		client(pipe2fd[0], pipe1fd[1]);

		// 等待子进程终止
		if (waitpid(childpid, NULL, 0) == -1) {
			perror("waitpid");
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);
	}

	return 0;
}



