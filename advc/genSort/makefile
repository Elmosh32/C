# makefile for generic bubbleSort

TARGET= genericSort
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= main.o genSort.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c ADTDefs.h
	$(CC) $(CFLAGS) -c main.c

genSort.o: genSort.c genSort.h
	$(CC) $(CFLAGS) -c genSort.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
