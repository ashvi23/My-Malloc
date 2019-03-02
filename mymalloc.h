#include <stdio.h>
#include <stdlib.h>
#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)
    char myMem[4096];
    void* mymalloc(int, __FILE__, __LINE__);
    void myfree(void*, __FILE__, __LINE__);
