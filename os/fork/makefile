# makefile for generic heap

TARGET= fork
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= fork.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: fork.c
	$(CC) $(CFLAGS) -c fork.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
