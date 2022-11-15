# makefile for generic heap

TARGET= genericHashSet
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS=  mainHashSet.o genHashSet.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm

mainHashSet.o: mainHashSet.c 
	$(CC) $(CFLAGS) -c mainHashSet.c

genHashSet.o: genHashSet.c genHashSet.h
	$(CC) $(CFLAGS) -c genHashSet.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
