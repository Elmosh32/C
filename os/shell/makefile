# makefile for generic heap

TARGET= shell
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= shell.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
