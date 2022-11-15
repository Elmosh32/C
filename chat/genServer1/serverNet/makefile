#makefile ClientManager

TARGET = MainServerManager.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = ServerManager.o serverNet.o userManager.o user.o protocol.o
#LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/guy/prog/GENDS/ 
#export LD_LIBRARY_PATH

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -L/home/moshe-elazar/Desktop/experis/advc/genDS -lgenDL 

serverNet.o:serverNet.c serverNet.h  
	$(CC) $(CFLAGS) -c serverNet.c 

ServerManager.o:ServerManager.c  ../protocol/protocol.h 
	$(CC) $(CFLAGS) -c ServerManager.c 

userManager.o:userManager.c userManager.h
	$(CC) $(CFLAGS) -c userManager.c 
	
user.o:user.c user.h
	$(CC) $(CFLAGS) -c user.c 

protocol.o: ../protocol/protocol.c  ../protocol/protocol.h 
	$(CC) $(CFLAGS) -c ../protocol/protocol.c 
	
debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

