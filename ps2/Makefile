# variables
CC=gcc
CFLAGS=-std=c11 -Wall
LDLIBS=-lm
OUTPUT=game

# targets
all: $(OUTPUT)

$(OUTPUT): hof.o k.o ui.o main.o
	$(CC) $(CFLAGS) hof.o k.o ui.o main.o $(LDLIBS) -o $(OUTPUT)

hof.o: hof.c hof.h
	$(CC) $(CFLAGS) -c hof.c $(LDLIBS) -o hof.o

k.o: k.c k.h
	$(CC) $(CFLAGS) -c k.c $(LDLIBS) -o k.o

ui.o: ui.c ui.h k.h
	$(CC) $(CFLAGS) -c ui.c $(LDLIBS) -o ui.o

main.o: main.c ui.h k.h
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

# remove compiled files
clean:
	rm -rf $(OUTPUT) *.o
