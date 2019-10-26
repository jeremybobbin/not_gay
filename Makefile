run: build
	./a.out

build: main.c
	cc main.c
