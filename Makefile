all: main

main: 
	gcc access.c LISTA.C page.c main.c -lm -o sim-virtual

clean:
	$(RM) sim-virtual 
