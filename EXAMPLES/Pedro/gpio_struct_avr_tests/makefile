HEADERS = main.h

default: program

program.o: main.c $(HEADERS)
	gcc -c main.c -o program.o

program: program.o
	gcc program.o -o program

clean:
	-rm -f program.o
	-rm -f program
