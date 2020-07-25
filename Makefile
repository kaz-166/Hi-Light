LFSR: main.o lfsr.o
	gcc -o lfsr main.o lfsr.o -lm
main.o: main.c
	gcc -c main.c
lfsr.o: lfsr.c
	gcc -c lfsr.c
