#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "access.h"
#include "sim.h"

#define ESCAPE(); printf("%s",manual);return 0;





int main(int argc, const char *argv[])
{
	Access* accesses;
    int num_accesses;
	int algorithm_mode;
	int page_size;
    int memory_size;
	
    if(argc < 5) {
        ESCAPE();
    }
	algorithm_mode = getAlgorithmMode(argv[1]);
	page_size = atol(argv[3]);
    memory_size = atol(argv[4]);

    if(algorithm_mode == -1){
        printf("Algorithm mode not acceptable.");
        ESCAPE();
    }
    
    accesses = readLog(argv[2],&num_accesses);
    if(accesses == NULL){
        printf("Log format not acceptable.");
        ESCAPE();
    } 
    
    //check boundaries
    if(!(page_size > 0)){
        printf("Page size either is not an integer or is 0.");
        ESCAPE();
    }
    if(!(memory_size > 0)){
        printf("Memory size either is not an integer or is 0.");
        ESCAPE();
    }
	printf("initializing simulation...\n");
    simulate(algorithm_mode, accesses, num_accesses, page_size, memory_size);

    return 0;
}
