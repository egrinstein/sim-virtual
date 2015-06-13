#ifndef ACCESSH
#define ACCESSH

typedef struct access{
    unsigned int address;
    char mode;
} Access;

Access* readLog(const char* path,int* num);
#endif
