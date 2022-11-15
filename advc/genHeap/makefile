# makefile for generic heap

TARGET= genericHeap
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS=  genVector.o genHeap.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

genVector.o: ../genVec/genVector.c ../genVec/genVector.h
	$(CC) $(CFLAGS) -c ../genVec/genVector.c

genHeap.o: genHeap.c genHeap.h
	$(CC) $(CFLAGS) -c genHeap.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
