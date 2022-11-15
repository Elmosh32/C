# makefile sample

TARGET= sort
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= vector.o sorting.o mainSort.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c

sorting.o: sorting.c sorting.h
	$(CC) $(CFLAGS) -c sorting.c

mainSort.o: mainSort.c
	$(CC) $(CFLAGS) -c mainSort.c

clean:
	rm -f $(TARGET) $(OBJS)
