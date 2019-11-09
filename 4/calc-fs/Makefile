run: a.out
	./a.out

a.out: calc.h getch.c getop.c main.c stack.c 
	tcc -lm getch.c getop.c main.c stack.c 
