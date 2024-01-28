#variables
CC=gcc
CFLAGS=-std=c11 -Werror -Wall -Wconversion
LDLIBS=-lm
CHECK=cppcheck --enable=performance,unusedFunction
CPPFLAGS=--error-exitcode=1
OUTPUT=adventure

#targets
all: $(OUTPUT)

$(OUTPUT): main.o backpack.o command.o container.o game.o item.o parser.o room.o world.o
	$(CC) $(CFLAGS) main.o backpack.o command.o container.o game.o item.o parser.o room.o world.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS)

backpack.o: backpack.c backpack.h
	$(CC) $(CFLAGS) -c backpack.c $(LDLIBS)

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c $(LDLIBS)

container.o: container.c container.h
	$(CC) $(CFLAGS) -c container.c $(LDLIBS)

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c $(LDLIBS)

item.o: item.c item.h
	$(CC) $(CFLAGS) -c item.c $(LDLIBS)

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c $(LDLIBS)

room.o: room.c room.h
	$(CC) $(CFLAGS) -c room.c $(LDLIBS)

world.o: world.c world.h
	$(CC) $(CFLAGS) -c world.c $(LDLIBS)

#remove compiled files
clean: 
	rm -rf $(OUTPUT) *.o
