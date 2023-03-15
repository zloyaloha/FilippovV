
CCFLAGS = -Wall -pedantic -std=c99
prog: sort.o stack.o main.o
	gcc -o prog main.o sort.o stack.o
main.o: main.c
	gcc $(CCFLAGS) -c main.c
stack.o: stack.c stack.h
	gcc $(CCFLAGS) -c stack.c
sort.o: sort.c sort.h
	gcc $(CCFLAGS) -c sort.c
clean:
	rm -f *.o *.out prog