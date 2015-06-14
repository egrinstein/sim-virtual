#include "access.h"
#include "page.h"
#include "sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LISTA.H"
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

	int * pageIndexes;
	Page * pageTable;
	LIS_tppLista ordered_pages;
	Page ** pagesInMemory;
	int num_pages = memory_size/page_size;
	int i; //i as worldclock
    int interrupt_dt = 0;
    int dt = 0;
	int page_faults = 0;
	int pages_written_to_disk = 0;
	
    switch(mode){
    	case 0:
			break;
		case 1:
			break;
		case 2: 
			ordered_pages = LIS_CriarLista( NULL );
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
		Page * new_page;
		Access curr_access = accesses[i];
		
		int curr_page_index = getAddress(curr_access.address,page_size);

		
        dt = i-dt;
        interrupt_dt = interrupt_dt + dt;
        if(interrupt_dt >= INTERRUPT){
            clock_update(pagesInMemory,num_pages);
            interrupt_dt = 0;
        }

		
		
		aux_index = access_index(pageIndexes,num_pages,curr_page_index,&aux_flag);

		if (aux_flag <= 0){ //page fault!
			page_faults++; 
			
			//if theres free memory, it wont execute the "if" below.
			if (aux_flag == -1){
				Page * aux_page;
			
				/* NRU specific */
				if (mode == 1){
					aux_index = evict_NRU(pagesInMemory, pageIndexes, num_pages);
				}
				/* SEG specific */
				else if (mode == 2){
					aux_index = evict_SEG(pagesInMemory, pageIndexes, num_pages,ordered_pages);
					if (aux_index == -1){
						printf("SEG algorithm Failed.\n");
						exit(1);
					}
					
				}
					
				aux_page = &pageTable[pageIndexes[aux_index]];

				if (aux_page->m == 1){
                    pages_written_to_disk++;
				}
                aux_page->m = 0;
                aux_page->r = 0;

			}
			new_page = &pageTable[pageIndexes[aux_index]];
			pageIndexes[aux_index] = curr_page_index;	
			pagesInMemory[aux_index] = new_page;

			/*SEG specific*/
			if (mode == 2){
				IrFinalLista( ordered_pages );
				LIS_InserirElementoApos( ordered_pages,(void*) pagesInMemory[aux_index]);
			}

		}
		new_page = &pageTable[pageIndexes[aux_index]];

		


		//INFO UPDATE (always executed)::
		
		new_page->last_access = i;
		if(accesses[i].mode == 'W'){
            new_page->m = 1;
		}
        new_page->r = 1; //it always changes r to 1 (see NRU).
    }
	printf("Pages written to disk: %d\nPage Faults: %d\n",pages_written_to_disk,page_faults);

}
