#include <string.h>

const char manual[] = 
    "\n4 arguments:\nThe Algorithm Mode: \"LRU\", \"NRU\" or \"SEG\"\nThe unix path to an access log\nThe page size in KB (8 < integer < 32)\nThe physical memory size in KB (128 < integer < 16384)\n"
;

int getAlgorithmMode(const char* mode){
    //when altering here, don't forget of updating the manual and sim.c
	const char *algorithm_modes[3];	
    int num_modes = 3;
    int i;
	algorithm_modes[0] = "LRU";
	algorithm_modes[1] = "NRU";
	algorithm_modes[2] = "SEG";
    for(i = 0;i<num_modes;i++){
        if(strcmp(algorithm_modes[i],mode)==0){          
		   return i;
		}
    }
    return -1;
}
