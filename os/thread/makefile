# makefile for generic heap

TARGET= thread
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= thread.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: thread.c
	$(CC) $(CFLAGS) -c thread.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
