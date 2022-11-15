# makefile for generic heap

TARGET= genericBst
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= genBst.o mainGenBst.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

mainGenBst.o: mainGenBst.c 
	$(CC) $(CFLAGS) -c mainGenBst.c

genBst.o: genBst.c 
	$(CC) $(CFLAGS) -c genBst.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
