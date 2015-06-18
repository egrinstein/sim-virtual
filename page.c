#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "page.h"

unsigned int m_log2( unsigned int x )
{
  //return (int) log( x ) / log( 2. );
  unsigned int ans = 0 ;
  while( x>>=1 ) ans++;
  return ans ;
}

int getAddress(unsigned int addr,int page_size){
    unsigned int shift = m_log2(page_size << 10);
    return addr >> (shift );

}

static int getPageClass(Page * page){ 
	int class = 0;
	if (page->r){
		class+=2;
	}
	if (page->m){
		class+=1;
	}
	return class;
}


Page * createPageTable(int page_size){
	int i;
    int table_size;
	Page *aux_page;
	Page *pageTable ;
	unsigned int space = m_log2(page_size << 10);

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





void clock_update(Page ** pagesInMemory , int num_pages )
{
    int i;
    for(i = 0; i < num_pages; ++i) {
        if(pagesInMemory[i]) {
			pagesInMemory[i]->r = 0;
        }
    }
}

void update_page_ages(Page ** pagesInMemory, unsigned int * pageAges, int num_pages){
	int i;
	
	for (i=0;i<num_pages;i++){

		if (!pagesInMemory[i]) continue;

		pageAges[i] = pageAges[i] >> 1;
	}

}


int evict_LRU(Page ** pagesInMemory ,  int * pageIndexes, int num_pages ,unsigned int * pageAges){ 
	int i,
		min_age_index = -1;
	unsigned int min_age = UINT_MAX;
	for (i=0;i<num_pages;i++){
		if ( pageAges[i] < min_age ){
			min_age = pageAges[i];
			min_age_index = i;
		}
	}
	return min_age_index;


}

int evict_NRU(Page ** pagesInMemory ,int * pageIndexes, int num_pages){
	int i;
	int first_to_check;
	

	int lowest_class_index = -1;
	int lowest_class_seen = 4; // 4 is bigger than any class.

	
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

int evict_SEG(Page ** pagesInMemory ,  int * pageIndexes, int num_pages , LIS_tppLista ordered_pages ){

	Page * oldest_page_suitable;
	int i;
	IrInicioLista( ordered_pages );
	
	oldest_page_suitable = (Page *) LIS_ObterValor( ordered_pages );
	while (oldest_page_suitable->r == 1){
		LIS_ExcluirElemento( ordered_pages );
		IrFinalLista( ordered_pages );
		LIS_InserirElementoApos(ordered_pages,(void *)oldest_page_suitable);
		oldest_page_suitable->r = 0;
		IrInicioLista( ordered_pages );
		oldest_page_suitable = (Page *) LIS_ObterValor( ordered_pages );
	}
	LIS_ExcluirElemento( ordered_pages );

	for (i=0;i<num_pages;i++){
		if (pagesInMemory[i] == oldest_page_suitable)
			return i;
	} /* Bad for performance*/
	
	return -1;

}

