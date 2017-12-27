all: mainpipe

mainpipe: mainpipe.o server.o client.o
	gcc -g -o mainpipe mainpipe.o server.o client.o

mainpipe.o: mainpipe.c
	gcc -g -c mainpipe.c

server.o: server.c server.h
	gcc -g -c server.c

client.o: client.c client.h
	gcc -g -c client.c

clean:
	rm mainpipe mainpipe.o server.o client.o
