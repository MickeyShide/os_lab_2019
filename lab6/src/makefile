CC=gcc
DEPS=add.h
all: client server

client: client.c add
	$(CC) client.c add.o -o client -pthread

server: server.c add
	$(CC) server.c add.o -pthread  -o server

add: add.c add.h
	$(CC) -c add.c -o add.o

clean :
	rm client server