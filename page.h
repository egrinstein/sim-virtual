#ifndef PAGEH
#define PAGEH

typedef struct page Page;

int getAddress(unsigned int addr,int pagesize);

Page * createPageTable(int page_size);

Page ** createMemory(int num_pages);

int evict_SEG(Page ** pagesInMemory , int num_pages );

int evict_LRU(Page ** pagesInMemory , int num_pages );

int evict_NRU(Page ** pagesInMemory , int num_pages );

void update_SEG(Page ** pagesInMemory , int num_pages );

void update_LRU(Page ** pagesInMemory , int num_pages );

void update_NRU(Page ** pagesInMemory , int num_pages );

#endif
