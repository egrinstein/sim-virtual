#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct page{
    int last_access;
	int r;
	int m;

	int corresponding_frame;
	
	long reference_counter; //for LRU    
} Page;




int getAddress(unsigned int addr,int pagesize){
    int shift = log( pagesize << 10 ) / log( 2. );
    //MS does not provide log2()
    return addr << shift;
}


Page * createPageTable(int pages_size)
{
	int i;
    int pageBits = getAddress(pageSize);
    int tableSize = pow(2, 32 - pageBits);
	Page *auxPage;
    Page *pageTable = (Page*)malloc(pageTableSize * sizeof(Page));

	auxPage = pageTable;
	
    for (i=0;i<tableSize;i++){
		auxPage->lastAccess = 0; //seila
		auxPage->r = 0;
		auxPage->m = 0;
		auxPage->reference_counter = 0; //tlvz suma depois
		auxPage++; //funciona???Anda 1 pagina ou 1 byte?
	}

    return pageTable;
}

Page ** createMemory(int num_pages){
    Page **pagesInMemory = (Page**)malloc( num_pages * sizeof(Page*));

    if(!pageVector) {
        printf("Not enough memory to simulate page vector.\n");
        return NULL;
    }
    int i;
    for(i = 0; i < *nPageVector; ++i)
        pageVector[i] = NULL;
    return pagesInMemory;
}


Page * evict_NRU(Page ** pagesInMemory , int num_pages ){
	int i,
		class;
	
	srand( (unsigned)time(NULL) );

	Page * lowest_class_page_seen = NULL;
	char lowest_class_seen = 4; // 4 is bigger than any class.

	
	int first_to_check = rand()%num_pages;

	for (i=0;i<num_pages;i++){
		int index = (first_to_check + i)%num_pages;
		Page * current_page = pagesInMemory + index*sizeof(Page);
		int curr_class = getPageClass(current_page)
		if ( curr_class < lowest_class_seen ){
			if ( curr_class == 0 ) return current_page;
			lowest_class_seen = curr_class;
			lowest_class_page_seen = current_page;	
		}
			
	}	
	return current_page;
	
}

Page * evict_SEG(Page ** pagesInMemory , int num_pages ){}

Page * evict_LRU(Page ** pagesInMemory , int num_pages ){}


static char getPageClass(Page * page){ 
	return 2*page->m + page->r;
}




