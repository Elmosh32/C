TARGET= tests.out
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= mainHashMap.o mainGenVec.o mainGenQue.o mainGenHeap.o list_functions_main.o genDoubleListMain.o main.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -L/home/moshe-elazar/Desktop/experis/advc/genDS -lgenDL -lm

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

mainHashMap.o: mainHashMap.c 
	$(CC) $(CFLAGS) -c mainHashMap.c

mainGenVec.o: mainGenVec.c 
	$(CC) $(CFLAGS) -c mainGenVec.c
	
mainGenQue.o: mainGenQue.c 
	$(CC) $(CFLAGS) -c mainGenQue.c

mainGenHeap.o: mainGenHeap.c 
	$(CC) $(CFLAGS) -c mainGenHeap.c

list_functions_main.o: list_functions_main.c 
	$(CC) $(CFLAGS) -c list_functions_main.c

genDoubleListMain.o: genDoubleListMain.c 
	$(CC) $(CFLAGS) -c genDoubleListMain.c

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
