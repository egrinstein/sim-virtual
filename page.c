#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "page.h"

unsigned int log2( unsigned int x )
{
  unsigned int ans = 0 ;
  while( x>>=1 ) ans++;
  return ans ;
}

int getAddress(unsigned int addr,int page_size){
    //int shift = (int) log( page_size << 10 ) / log( 2. );
    unsigned int shift = log2(page_size << 10);
    return addr >> (shift );
}

static char getPageClass(Page * page){ 
	return (page->m)*2 + page->r;
}


Page * createPageTable(int page_size){
	int i;
    int table_size;
	Page *aux_page;
	Page *pageTable ;
	unsigned int space = log2(page_size << 10);
	table_size = pow(2, 32 - space);
	pageTable = (Page*)malloc(table_size* sizeof(Page));
	
	aux_page = pageTable;
	
    for (i=0;i<table_size;i++){
		aux_page[i].last_access = 0; 
		aux_page[i].r = 0;
		aux_page[i].m = 0;
	}

    return pageTable;
}



Page ** createMemory(int num_pages){
	int i;
    Page **pagesInMemory = (Page**)malloc( num_pages * sizeof(Page*));
	
    if(!pagesInMemory) {
        printf("Not enough memory to simulate memory.\n");
        return NULL;
    }
   
	for(i = 0; i < num_pages; i++){
        pagesInMemory[i] = NULL;
	}
    return pagesInMemory;
}


void update_NRU(Page ** pages_in_memory , int num_pages)
{
    int i;
    for(i = 0; i < num_pages; ++i) {
        if(pages_in_memory[i]) {
			pages_in_memory[i]->r = 0;
        }
    }
}
int evict_NRU(Page ** pagesInMemory ,int * pageIndexes, int num_pages ){
	int i,
		class;
	int first_to_check;
	

	int lowest_class_index = -1;
	char lowest_class_seen = 4; // 4 is bigger than any class.

	
	first_to_check = rand()%num_pages;
	srand( (unsigned)time(NULL) );
	
	for (i=0;i<num_pages;i++){
		int curr_class;
		int index = (first_to_check + i)%num_pages;
		Page * current_page = pagesInMemory[index];
		if (!current_page) continue;
		curr_class = getPageClass(current_page);
		if ( curr_class < lowest_class_seen ){
			if ( curr_class == 0 ) return index;
			lowest_class_seen = curr_class;
			lowest_class_index = index;	
		}
			
	}	
	return lowest_class_index;
	
}

int evict_SEG(Page ** pagesInMemory ,  int * pageIndexes, int num_pages ){return 0;}

void update_SEG(Page ** pagesInMemory , int num_pages ){ }

int evict_LRU(Page ** pagesInMemory ,  int * pageIndexes, int num_pages ){ return 0;}

void update_LRU(Page ** pagesInMemory , int num_pages ){ }




