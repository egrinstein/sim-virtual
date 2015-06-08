#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "access.h"
struct access{
    unsigned int address;
    char mode;
};

Access* readLog(const char* path,int* num){
    FILE * file = fopen(path, "r");
    if(file ==NULL) {
        printf("Invalid log filepath:\n\t%s\n", path);
        return NULL;
    }
    int num_lines = 0;
    unsigned int address;
    char mode;
    while(fscanf(file, "%x %c",&address,&mode)==2){
        num_lines = num_lines + 1;
        int digits = floor(log10(abs(address))) + 1;
        if(digits != 8){
            printf("Invalid address on line %d of \n\t%s\n",num_lines,path);
            return NULL;
        }
        if(!(mode == 'R' || mode == 'W')){
            printf("Invalid access mode on line %d of\n\t%s\n",num_lines,path);
            return NULL;
        }
    }
    if(!feof(file)){
        printf("Invalid trailing data. filepath:\n\t%s\n",path);
    }
    rewind(file);
    Access* log = malloc(num_lines*sizeof(Access));
    if(log == NULL){
        printf("File is too large. filepath:\n\t%s\n",path);
    } 
    int i;
    for(i = 0;i < num_lines;i++){
       fscanf(file,"%x %c",&log[i].address,&log[i].mode); 
    }
    *num = num_lines;
    return log; 
}
