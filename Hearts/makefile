# makefile for game hearts

TARGET= hearts
CC=gcc
CFLAGS= -ansi -g -pedantic -Wall -Wno-overlength-strings
OBJS= game.o round.o player.o deck.o heartsMain.o ui.o auxiliaryFunc.o vector.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

heartsMain.o: heartsMain.c
	$(CC) $(CFLAGS) -c heartsMain.c

deck.o: deck.c includes/deck.h
	$(CC) $(CFLAGS) -c deck.c

player.o: player.c includes/player.h
	$(CC) $(CFLAGS) -c player.c

round.o: round.c includes/round.h
	$(CC) $(CFLAGS) -c round.c

game.o: game.c includes/game.h
	$(CC) $(CFLAGS) -c game.c

ui.o: ui.c includes/ui.h
	$(CC) $(CFLAGS) -c ui.c

utilFuncs.o: auxiliaryFunc.c includes/auxiliaryFunc.h
	$(CC) $(CFLAGS) -c auxiliaryFunc.c

vector.o: vector.c includes/vector.h
	$(CC) $(CFLAGS) -c vector.c

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
