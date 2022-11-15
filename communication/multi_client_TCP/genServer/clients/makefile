TARGET= client.out
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= client.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

client.o: client.c ../include/serverClient.h
	$(CC) $(CFLAGS) -c client.c

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
