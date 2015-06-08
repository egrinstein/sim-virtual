#include <string.h>

const char manual[] = 
    "\n
    4 arguments:\n
    The Algorithm Mode: \"LRU\", \"NRU\" or \"SEG\"\n
    The unix path to an access log\n
    The page size in KB (integer > 0)\n
    The physical memory size in KB (integer > 0)\n
    "
;

int getAlgorithmMode(const char* mode){
    //when altering here, don't forget of updating the manual and sim.c
    const char algorithm_modes[][] = {"LRU","NRU","SEG"};
    int num_modes = 3;
    int i;
    for(i = 0;i<num_modes;i++){
        if(strcmp(algorithm_modes[i],mode)==0) 
            return i;
    }
    return -1;
}
