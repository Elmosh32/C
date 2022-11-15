# makefile for generic heap

TARGET= thread
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= semaphore.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

semaphore.o: semaphore.c
	$(CC) $(CFLAGS) -c semaphore.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
