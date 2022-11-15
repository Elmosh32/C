# makefile for generic heap

TARGET= libgenDL.so
CC=gcc
CFLAGS = -g -c -ansi -pedantic -fPIC 
OBJS= genVector.o genHeap.o genQueue.o genDoubleList.o list_itr.o list_functions.o genHashMap.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm -shared

genVector.o: ../genVec/genVector.c ../genVec/genVector.h
	$(CC) $(CFLAGS) -c ../genVec/genVector.c

genHeap.o: ../genHeap/genHeap.c ../genHeap/genHeap.h
	$(CC) $(CFLAGS) -c ../genHeap/genHeap.c

genQueue.o: ../genQueue/genQueue.c ../genQueue/genQueue.h
	$(CC) $(CFLAGS) -c ../genQueue/genQueue.c

genDoubleList.o: ../genDoubleList/genDoubleList.c ../genDoubleList/genDoubleList.h
	$(CC) $(CFLAGS) -c ../genDoubleList/genDoubleList.c

list_itr.o: ../genDoubleList/list_itr.c ../genDoubleList/list_itr.h
	$(CC) $(CFLAGS) -c ../genDoubleList/list_itr.c

list_functions.o: ../genDoubleList/list_functions.c ../genDoubleList/list_functions.h
	$(CC) $(CFLAGS) -c ../genDoubleList/list_functions.c

genHashMap.o: ../hash/hashMap/genHashMap.c ../hash/hashMap/genHashMap.h
	$(CC) $(CFLAGS) -c ../hash/hashMap/genHashMap.c

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)
	
debug: $(TARGET)
	gdb ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
