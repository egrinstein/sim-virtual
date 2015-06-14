#include <stdio.h>
#ifdef cleanout 
    #define DEBUG(...); (void)0;
#else
    #define DEBUG printf
#endif
#include <stdlib.h>
#include "config.h"
#include "access.h"
#include "sim.h"

#define ESCAPE(MSG); printf(MSG);printf("%s",manual);return 0;





int main(int argc, const char *argv[])
{
	Access* accesses;
    int num_accesses;
	int algorithm_mode;
	int page_size;
    int memory_size;
	
    if(argc < 5) {
        ESCAPE("\n");
    }
	algorithm_mode = getAlgorithmMode(argv[1]);
	page_size = atol(argv[3]);
    memory_size = atol(argv[4]);

    if(algorithm_mode == -1){
        ESCAPE("Algorithm mode not acceptable.");
    }
    
    accesses = readLog(argv[2],&num_accesses);
    if(accesses == NULL){
        ESCAPE("Log format not acceptable.");
    } 
    
    //check boundaries
    if(!(page_size > 0)){
        ESCAPE("Page size either is not an integer or is 0.");
    }
    if(!(page_size>8 ||page_size<32)){
        ESCAPE("Page size should be between 8 and 32 kb.");
    }
    if(!(memory_size > 0)){
        ESCAPE("Memory size either is not an integer or is 0.");
    }
    if(!(memory_size>8 ||memory_size<32)){
        ESCAPE("Page size should be between 128 and 16384 kb.");
    }
	DEBUG("initializing simulation...\n");
    simulate(algorithm_mode, accesses, num_accesses, page_size, memory_size);

    return 0;
}
