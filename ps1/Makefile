CFLAGS = -std=c11 -Wall -Werror
OUTPUT = ps1

all : $(OUTPUT)

$(OUTPUT): main.o bmp.o playfair.o
	gcc $(CFLAGS) main.o bmp.o playfair.o -lm -o $(OUTPUT)


main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o


bmp.o: bmp.c bmp.h
	gcc $(CFLAGS) -c bmp.c -o bmp.o


playfair.o: playfair.c playfair.h
	gcc $(CFLAGS) -c playfair.c -o playfair.o


clean:
	rm -rf *.o ps1