TARGET= server.out
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= server.o main.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -L/home/moshe-elazar/Desktop/experis/advc/genDS -lgenDL 

main.o: main.c ../include/serverClient.h
	$(CC) $(CFLAGS) -c main.c

server.o: server.c ../include/serverClient.h
	$(CC) $(CFLAGS) -c server.c

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
