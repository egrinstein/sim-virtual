#ifndef PAGEH
#define PAGEH
#include "lista.h"

typedef struct page{
	int last_access;
	int r;
	int m;


} Page;


int getAddress(unsigned int addr,int pagesize);

Page * createPageTable(int page_size);

Page ** createMemory(int num_pages);

int evict_LRU(Page ** pagesInMemory ,  int * pageIndexes, int num_pages , unsigned int * pageAges);

int evict_NRU( Page ** pagesInMemory , int * pageIndexes, int num_pages );

int evict_SEG(Page ** pagesInMemory ,  int * pageIndexes, int num_pages , LIS_tppLista ordered_pages );

void clock_update(Page ** pagesInMemory , int num_pages );

void update_page_ages(Page ** pagesInMemory, unsigned int * pageAges, int num_pages);

#endif
