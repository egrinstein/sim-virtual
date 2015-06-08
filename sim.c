#include "access.h"

void simulate(int mode, Access* accesses, int num_accesses, int page_size, int memory_size){
    
    switch(mode){
    
    }
    //do the function pointer thing 

    //initialize array of pages
    //initialize memory (array of pointers to pages)
    int i;
    #define INTERRUPT 50
    int interrupt_dt = 0;
    int dt = 0;
    //i as worldclock
    for(i = 0; i < num_accesses; i++){
        dt = i-dt;
        interrupt_dt = interrupt_dt + dt;
        if(interrupt_dt >= INTERRUPT){
            //update pages
            interrupt_dt = 0;
        }
        //look for address in current page
        //do a page fault or update its info
    }
    
}
