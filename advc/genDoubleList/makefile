# makefile for generic heap

TARGET= genericHeap
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= list_functions.o genDoubleList.o list_itr.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

genVector.o: genDoubleList.c genDoubleList.h
	$(CC) $(CFLAGS) -c genDoubleList.c

list_itr.o: list_itr.c list_itr.h
	$(CC) $(CFLAGS) -c list_itr.c

list_functions.o: list_functions.c list_functions.h
	$(CC) $(CFLAGS) -c list_functions.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
