#include "access.h"
#include "page.h"
#include "sim.h"
#include <stdio.h>
#include <stdlib.h>
#define INTERRUPT 100


static int access_index(int * pageIndexes, int num_pages, unsigned int index, int * return_flag){
	int i;
	int free_index = -1;

	for (i=0;i<num_pages;i++){
		if (pageIndexes[i] == -1){
			*return_flag = 0;
			free_index = i;
		}
		if (index == pageIndexes[i]){
			*return_flag = 1;
			return i;
		}
	}
	if (free_index != -1) return free_index;

	*return_flag = -1;
	return -1;
}//returns the index of the page when it finds it, the index of a free page or -1 when needs eviction

void simulate(int mode, Access* accesses, int num_accesses, int page_size, int memory_size){

	unsigned int (*evict_algorithm)(Page**, int*, int);
    void (*update_algorithm)(Page**, int);
	int * pageIndexes;
	Page * pageTable;
	Page ** pagesInMemory;
	int num_pages = memory_size/page_size;
	int i; //i as worldclock
    int interrupt_dt = 0;
    int dt = 0;
	int aux_index;
	int page_faults = 0;
	int pages_written_to_disk = 0;
	
    switch(mode){
    	case 0:
			evict_algorithm = evict_LRU;
			update_algorithm = update_LRU;
			break;
		case 1:
			evict_algorithm = evict_NRU;
			update_algorithm = update_NRU;
			break;
		case 2: 
			evict_algorithm = evict_SEG;
			update_algorithm = update_SEG;
			break;
		default:
			printf("Unknown algorithm\n");
			return;
    }
	printf("creating page table...\n");
	pageTable = createPageTable(page_size);
	if (!pageTable){
		printf("Could not create page table");
		return ;
	} 
	
	printf("creating simulated memory...\n");
	pagesInMemory = createMemory(num_pages);
	if (!pagesInMemory){
		printf("Could not create Memory");
		return ;
	} 

	pageIndexes = malloc(num_pages*sizeof(int));
	if (!pageIndexes){
		printf("Could not create Page Indexes");
		return ;
	} 
	memset(pageIndexes,-1,num_pages*sizeof(int));
	
    for(i = 0; i < num_accesses; i++){
		
		int aux_index,
			aux_flag;
		Access curr_access = accesses[i];
		int curr_page_index = getAddress(accesses[i].address,page_size);
		
        dt = i-dt;
        interrupt_dt = interrupt_dt + dt;
        if(interrupt_dt >= INTERRUPT){
            update_algorithm(pagesInMemory,num_pages);
            interrupt_dt = 0;
        }
		
		
		aux_index = access_index(pageIndexes,num_pages,curr_page_index,&aux_flag);

		if (aux_flag <= 0){ //page fault!
			page_faults++; // escrever pela primeira vez é page fault tbm?
			
			//if theres free memory, it wont execute the "if" below.
			if (aux_flag == -1){
				Page * aux_page;
				
				aux_index = evict_algorithm(pagesInMemory, pageIndexes, num_pages);
				aux_page = &pageTable[pageIndexes[aux_index]];
				
				if (aux_page->m == 1){
                    pages_written_to_disk++;
				}
                aux_page->m = 0;
                aux_page->r = 0;

			}

			pageIndexes[aux_index] = curr_page_index;	
			pagesInMemory[aux_index] = &pageTable[pageIndexes[aux_index]];

		}


		//INFO UPDATE (always executed)::
		pageTable[pageIndexes[aux_index]].last_access = i;
		if(accesses[i].mode == 'W'){
            pageTable[pageIndexes[aux_index]].m = 1;
		}
        pageTable[pageIndexes[aux_index]].r = 1; //it always changes r to 1 (see NRU).
    }
	printf("Pages written to disk: %d\nPage Faults: %d\n",pages_written_to_disk,page_faults);
}
