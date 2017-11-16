all: tcpserver tcpclient

tcpserver: tcpserver.o
	gcc -g -o tcpserver tcpserver.o

tcpclient: tcpclient.o
	gcc -g -o tcpclient tcpclient.o

tcpserver.o: tcpserver.c
	gcc -g -c tcpserver.c

tcpclient.o: tcpclient.c
	gcc -g -c tcpclient.c

clean: all
	rm all
