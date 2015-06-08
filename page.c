#include <math.h>

struct page{
    int last_access;
    char read,write;
};


int getAddress(unsigned int addr,int pagesize){
    int shift = log( pagesize << 10 ) / log( 2. );
    //MS does not provide log2()
    return addr << shift;
}

