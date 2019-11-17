run: eval
	./eval

eval: calc.h getop.c main.c stack.c 
	tcc -lm getop.c main.c stack.c -o eval
