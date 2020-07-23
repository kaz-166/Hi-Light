LFSR: main.o 
	gcc -o lfsr main.o -lm
main.o: main.c
	gcc -c main.c
