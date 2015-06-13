#include "access.h"
#include "page.h"
#include <stdio.h>
#include <stdlib.h>
#define INTERRUPT 50

void simulate(int mode, Access* accesses, int num_accesses, int page_size, int memory_size){

	int (*replaceAlgorithm)(Page*, int*, int);
    //int (*getPageVectorRemoveIndex)(PageTable*, int*, int);
	Page * pageTable;
	int * pagesInMemory;
	int * pageBits = 
	int num_pages = memory_size/page_size;
	int i; //i as worldclock
    int interrupt_dt = 0;
    int dt = 0;

    Access * access;
	int num_accesses;

    switch(mode){
    	case 0:
			replaceAlgorithm = LRU;
		case 1:
			replaceAlgorithm = NRU;
		case 2: 
			replaceAlgorithm = SEG;
		default:
			printf("Unknown algorithm");
			return;
    }
	
	pageTable = createPageTable(page_size);
	if (!pageTable)
		return -1;	

	pagesInMemory = createMemory(num_pages);	
	access = readLog("compilador.txt", &num_accesses);

    
    for(i = 0; i < num_accesses; i++){
		Access * curr_access = access[i];
		int curr_page_index = getAddress(access[i]->address,page_size);
        dt = i-dt;
        interrupt_dt = interrupt_dt + dt;
        if(interrupt_dt >= INTERRUPT){
            //update pages
            interrupt_dt = 0;
        }
        //look for address in current page
        //do a page fault or update its info
    }
    
}
