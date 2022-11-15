# makefile for generic bubbleSort

TARGET= genericSort
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= genVector.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

genVector.o: genVector.c genVector.h
	$(CC) $(CFLAGS) -c genVector.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
