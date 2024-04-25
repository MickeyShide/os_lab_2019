CC = gcc
CFLAGS = -pthread

all: psum

psum: parallel_sum.o
	$(CC) $(CFLAGS) parallel_sum.o -o psum

parallel_sum.o: parallel_sum.c
	$(CC) $(CFLAGS) -c parallel_sum.c

clean:
	rm -f *.o psum