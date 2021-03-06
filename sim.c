#include "access.h"
#include "page.h"
#include "sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#define INTERRUPT 80
#ifdef cleanout 
    #define DEBUG(...); (void)0;
#else
    #define DEBUG printf
#endif


static int access_index(int * pageIndexes, int num_frames, unsigned int index, int * return_flag){
	int i;
	int free_index = -1;

	for (i=0;i<num_frames;i++){
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

int simulate(int mode, Access* accesses, int num_accesses, int page_size, int memory_size,int * pages_written){

	int * pageIndexes;
	Page * pageTable;	
	Page ** pagesInMemory;
	int num_frames = memory_size/page_size;
	int i; //i as worldclock
    int interrupt_dt = 0;
    int dt = 0;
	int page_faults = 0;
	int pages_written_to_disk = 0;

	/* LRU specific data*/
	unsigned int * pageAges;

	/* SEG specific data*/
	LIS_tppLista ordered_pages;
	
	
    switch(mode){
    	case 0:
			pageAges = (int *)malloc(num_frames*sizeof(int));
			memset(pageAges,0,num_frames*sizeof(int));
			break;
		case 1:
			break;
		case 2: 
			ordered_pages = LIS_CriarLista( NULL );
			break;
		default:
			DEBUG("Unknown algorithm\n");
			return;
    }
	DEBUG("creating page table...\n");
	pageTable = createPageTable(page_size);
	if (!pageTable){
		DEBUG("Could not create page table");
		return ;
	} 
	
	DEBUG("creating simulated memory...\n");
	pagesInMemory = createMemory(num_frames);
	if (!pagesInMemory){
		DEBUG("Could not create Memory");
		return ;
	} 

	pageIndexes = malloc(num_frames*sizeof(int));
	if (!pageIndexes){
		DEBUG("Could not create Page Indexes");
		return ;
	} 
	memset(pageIndexes,-1,num_frames*sizeof(int));
	
	


    for(i = 0; i < num_accesses; i++){
		
		int aux_index,
			aux_flag;
		Page * new_page;
		Access curr_access = accesses[i];
		
		int curr_page_index = getAddress(curr_access.address,page_size);

		
        if(i%INTERRUPT == 0){
			/* LRU specific */
			if (mode == 0){
				update_page_ages(pagesInMemory,pageAges,num_frames);
			}

            clock_update(pagesInMemory,num_frames);
			   
        }

		
		
		aux_index = access_index(pageIndexes,num_frames,curr_page_index,&aux_flag);

		if (aux_flag <= 0){ //page fault!
			page_faults++; 
			
			//if theres free memory, it wont execute the "if" below.
			if (aux_flag == -1){
				Page * aux_page;
				
				switch(mode){
					case 0:
						aux_index = evict_LRU(pagesInMemory, pageIndexes, num_frames, pageAges);
						break;		
					case 1:
						aux_index = evict_NRU(pagesInMemory, pageIndexes, num_frames);
						break;
					case 2:
						aux_index = evict_SEG(pagesInMemory, pageIndexes, num_frames,ordered_pages);
						break;
					
				}
					
				aux_page = &pageTable[pageIndexes[aux_index]];

				if (aux_page->m == 1){
                    pages_written_to_disk++;
				}
                aux_page->m = 0;
                aux_page->r = 0;

			}
			new_page = &pageTable[curr_page_index];
			pageIndexes[aux_index] = curr_page_index;	
			pagesInMemory[aux_index] = new_page;

			/*SEG specific*/
			if (mode == 2){
				IrFinalLista( ordered_pages );
				LIS_InserirElementoApos( ordered_pages,(void*) pagesInMemory[aux_index]);
			}

		}
		new_page = &pageTable[curr_page_index];

		/*LRU specific counter*/
		if (mode == 0){
			unsigned int increment;
			increment = 1 << (8*sizeof(int) - 1);
			pageAges[aux_index] = pageAges[aux_index] + increment;
		}		


		//INFO UPDATE (always executed)::
		
		new_page->last_access = i;
		if(accesses[i].mode == 'W'){
            new_page->m = 1;
		}
        new_page->r = 1; //it always changes r to 1 (see NRU).
    }
	
    #ifdef cleanout
        //printf("%d,%d\n",page_faults,pages_written_to_disk);
    #else
        DEBUG("Pages written to disk: %d\nPage Faults: %d\n",pages_written_to_disk,page_faults);
    #endif
	*pages_written = pages_written_to_disk;
	return page_faults;
}
