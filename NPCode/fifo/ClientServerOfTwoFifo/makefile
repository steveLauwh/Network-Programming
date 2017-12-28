all: mainfifo

mainfifo: mainfifo.o server.o client.o
	gcc -g -o mainfifo mainfifo.o server.o client.o

mainfifo.o: mainfifo.c
	gcc -g -c mainfifo.c

server.o: server.c server.h
	gcc -g -c server.c

client.o: client.c client.h
	gcc -g -c client.c

clean:
	rm mainfifo mainfifo.o server.o client.o
