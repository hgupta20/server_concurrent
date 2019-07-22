all: server server_concurrent

server_concurrent: server.c csapp.o
	gcc  -o server_concurrent -D CONCURRENT server.c csapp.o

server: server.c csapp.o
	gcc -o server server.c csapp.o

csapp.o: csapp.h csapp.c
	gcc -c csapp.c

clean: 
	rm server server_concurrent csapp.o