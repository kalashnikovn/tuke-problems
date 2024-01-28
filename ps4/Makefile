CFLAGS= -std=c11 -Werror -Wall
OUTPUT = bmp

all: $(OUTPUT)
$(OUTPUT): main.c bmp.c bmp.h transformations.c transformations.h
	$(CC) $(CFLAGS) main.c bmp.c transformations.c -lm -o $(OUTPUT)

hof.o: bmp.c bmp.h
	gcc $(CFLAGS) -lm -c bmp.c -o bmp.o

k.o: transformations.c transformations.h
	gcc $(CFLAGS) -lm -c transformations.c -o transformations.o

main.o: main.c
	gcc $(CFLAGS) -lm -c main.c -o main.o

clean:
	rm -rf $(OUTPUT) *.0