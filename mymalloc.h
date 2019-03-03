#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)

    char myMem[4096];
    void* mymalloc(int, char *filename, int linenum);
    void myfree(void*, char *filename, int linenum);
    int bitadd(unsigned char high11, unsigned char low11, unsigned char high22, unsigned char low22);
    int bitsub(unsigned char high11, unsigned char low11, unsigned char high22, unsigned char low22);
    void combineBoth(char* prev, char* curr, char* next);
    void combineNext(char* curr, char* next);
    void combinePrev(char* curr, char* prev);
    int getbit(int num, int position);
    char getsizebits(char bits);
    int bin2int(char highbyte, char lowbyte);
    char* mallocTraverse(char* curr, int dataSize);
    void setInUse(int inUse, char* hiMeta);
    void splitBin(unsigned int currInt, char* hiMeta, char* loMeta);
    char* splitBlock(char* curr, int blockSize, int dataSize);
    char* bootStrap(char* ptr, char* hi, char* lo, int usrBlock);//set key, initialize first metadata
