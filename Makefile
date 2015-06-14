all: main

main: 
	 gcc -o sim-virtual *.c *.h -lm


clean:
	$(RM) sim-virtual 
