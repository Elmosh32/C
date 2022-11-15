TARGET= executor.out
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= executorMain.o executor.o task.o time.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -L/home/moshe-elazar/Desktop/experis/advc/genDS -lgenDL -lm

executorMain.o: executorMain.c
	$(CC) $(CFLAGS) -c executorMain.c

executor.o: executor.c executor.h
	$(CC) $(CFLAGS) -c executor.c

task.o: task.c task.h
	$(CC) $(CFLAGS) -c task.c

time.o: time.c time.h
	$(CC) $(CFLAGS) -c time.c

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
