# makefile for generic heap

TARGET= genericHeap
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS=  genQueue.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

genQueue.o: genQueue.c genQueue.h
	$(CC) $(CFLAGS) -c genQueue.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
