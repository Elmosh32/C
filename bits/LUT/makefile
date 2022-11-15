# makefile for generic heap

TARGET= lut.out
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall 
OBJS= lut.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

lut.o: lut.c
	$(CC) $(CFLAGS) -c lut.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
