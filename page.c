#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct page{
    int last_access;
	int r;
	int m;

	long reference_counter; //for LRU
    
} Page;



int getAddress(unsigned int addr,int pagesize){
    int shift = log( pagesize << 10 ) / log( 2. );
    //MS does not provide log2()
    return addr << shift;
}

static char getPageClass(Page * page){
	return 2*page->m + page->r;
}

int createPageTable(){

}


Page * createPageTable(int pageSize)
{
    int pageBits = getPageBits(pageSize);
    int pageTableSize = pow(2, 32 - pageBits);
    printfd("Page table entries: %d\n", pageTableSize);

    Page *pageTable = (PageTable*)malloc(pageTableSize * sizeof(PageTable));
    if(!pageTable) {
        printf("Not enough memory to simulate page table.\n");
        return NULL;
    }

    memset(pageTable, 0, pageTableSize * sizeof(PageTable));
    return pageTable;
}




int NRU(Page * pageTable, int num_pages ){
	int i,
		class;
	
	srand( (unsigned)time(NULL) );

	Page * lowest_class_page_seen = NULL;
	char lowest_class_seen = 4; // 4 is bigger than any class.

	
	int first_to_check = rand()%num_pages;
	for (i=0;i<num_pages;i++){
		int index = (first_to_check + i)%num_pages;
		Page * current_page = pageTable + index*sizeof(Page);
			
		if ( getPageClass(current_page) < lowest_class_seen ){
			lowest_class_seen = getPageClass(current_page);
			lowest_class_page_seen = current_page;	
		}
			
	}	
	//return INDEX_OF(lowest class page seen );
	//implement ^
	
}

int startSEG(){
	

}

int LRU(){
	

}

}







