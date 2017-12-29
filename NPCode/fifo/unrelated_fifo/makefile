# makefile 支持生成多个目标文件
all : clientmain servermain
.PHONY : all

clientmain: clientmain.o client.o
	gcc -g -o clientmain clientmain.o client.o

servermain: servermain.o server.o
	gcc -g -o servermain servermain.o server.o

clientmain.o: clientmain.c fifo.h
	gcc -g -c clientmain.c

servermain.o: servermain.c fifo.h
	gcc -g -c servermain.c

server.o: server.c server.h
	gcc -g -c server.c

client.o: client.c client.h
	gcc -g -c client.c

clean:
	rm clientmain.o servermain.o server.o client.o
