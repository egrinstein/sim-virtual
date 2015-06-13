#include <math.h>
#include <stdlib.h>
#include <time.h>

struct page{
	int last_access;
	int r;
	int m;
} ;




int getAddress(unsigned int addr,int pagesize){
    int shift = log( pagesize << 10 ) / log( 2. );
    //MS does not provide log2()
    return addr << shift;
}


Page * createPageTable(int page_size)
{
	int i;
    int pageBits = getAddress(pageSize);
    int tableSize = pow(2, 32 - pageBits);
	Page *auxPage;
    Page *pageTable = (Page*)malloc(pageTableSize * sizeof(Page));

	auxPage = pageTable;
	
    for (i=0;i<tableSize;i++){
		auxPage->lastAccess = 0; 
		auxPage->r = 0;
		auxPage->m = 0;
		auxPage->reference_counter = 0; //tlvz suma depois
		auxPage++; //funciona???Anda 1 pagina ou 1 byte?
	}

    return pageTable;
}



Page ** createMemory(int num_pages){
    PagesInMemory **pagesInMemory = (Page**)malloc( num_pages * sizeof(Page*));

    if(!pageVector) {
        printf("Not enough memory to simulate memory.\n");
        return NULL;
    }
    int i;
    for(i = 0; i < *num_pages; ++i)
        PagesInMemory[i] = NULL;
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
	
	srand( (unsigned)time(NULL) );

	int lowest_class_index = -1;
	char lowest_class_seen = 4; // 4 is bigger than any class.

	
	int first_to_check = rand()%num_pages;

	for (i=0;i<num_pages;i++){
		int index = (first_to_check + i)%num_pages;
		Page * current_page = pagesInMemory[index];
		int curr_class = getPageClass(current_page)
		if ( curr_class < lowest_class_seen ){
			if ( curr_class == 0 ) return pageIndexes[index];
			lowest_class_seen = curr_class;
			lowest_class_index = index;	
		}
			
	}	
	return lowest_class_index;
	
}

int evict_SEG(Page ** pagesInMemory , int num_pages ){return 0;}

void update_SEG(Page ** pagesInMemory , int num_pages ){ }

int evict_LRU(Page ** pagesInMemory , int num_pages ){ return 0;}

void update_LRU(Page ** pagesInMemory , int num_pages ){ }

static char getPageClass(Page * page){ 
	return 2*page->m + page->r;
}




