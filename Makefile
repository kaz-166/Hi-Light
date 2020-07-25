LFSR: main.o lfsr.o util.o
	gcc -o lfsr main.o lfsr.o util.o -lm
main.o: main.c
	gcc -c main.c
lfsr.o: lfsr.c
	gcc -c lfsr.c
util.o: util.c
	gcc -c util.c


