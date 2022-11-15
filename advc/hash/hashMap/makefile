# makefile for generic heap

TARGET= genericHeap
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= list_functions.o genDoubleList.o list_itr.o genHashMap.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm

genHashMap.o: genHashMap.c genHashMap.h
	$(CC) $(CFLAGS) -c genHashMap.c

genDoubleList.o: ../../genDoubleList/genDoubleList.c ../../genDoubleList/genDoubleList.h
	$(CC) $(CFLAGS) -c ../../genDoubleList/genDoubleList.c

list_itr.o: ../../genDoubleList/list_itr.c ../../genDoubleList/list_itr.h
	$(CC) $(CFLAGS) -c ../../genDoubleList/list_itr.c

list_functions.o: ../../genDoubleList/list_functions.c ../../genDoubleList/list_functions.h
	$(CC) $(CFLAGS) -c ../../genDoubleList/list_functions.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
