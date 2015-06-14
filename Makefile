all: main

main: 
	 gcc -o sim-virtual *.c *.h -lm

cleanout:
	 gcc -o sim-virtual *.c *.h -lm -Dcleanout
	
clean:
	$(RM) sim-virtual 
