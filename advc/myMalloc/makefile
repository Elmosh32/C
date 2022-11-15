# makefile for generic heap

TARGET= malooc.out
CC=gcc
CFLAGS = -g -c -ansi -pedantic 
OBJS= mallocMain.o myMalloc.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) 

mallocMain.o: mallocMain.c
	$(CC) $(CFLAGS) -c mallocMain.c

myMalloc.o: myMalloc.c myMalloc.h
	$(CC) $(CFLAGS) -c myMalloc.c

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)
	
debug: $(TARGET)
	gdb ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
