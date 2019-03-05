#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.c"
#include "mymalloc.h"
#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)

int main (int argc, char**argv){

/*
int*ptrarr2[150];
// case a
for(int i =0 ; i< 150; i++){
printf("inside case a\n");
  ptrarr2[i] = (int*) malloc(1);
  free(ptrarr2[i]);
ptrarr2[i] = NULL;
}
printf("case a done\n");

//case b
int *ptrarr[150];
int malcounter=0;
int *ptr;
for(int i =0; i< 150; i++){
 ptr = (int*) malloc(1);
 ptrarr[i] =ptr;
malcounter++;
}
for (int j =0; j<malcounter;j++ ){
  free(ptrarr[j]);
	ptrarr[j]=NULL;
}
printf("case b done\n");
*/
// case c
int malcounter = 0;
int freedptr = 0;
int ptr2free =-1;
int freeindex =0;
int* pointers[50];
int mallocindex =0;
  int random;
  while(malcounter <=50){
   random = rand()%2;
   printf("\n\n*************  START  *********************\n");
    printf("\nrandom: %d\n",random);
    if(random == 0){ //malloc if 0
      pointers[mallocindex] = (int*)malloc(1);
      malcounter++;
      mallocindex++;
      ptr2free =malcounter - freedptr;
    }
    else if (random == 1){ // free if 1
    printf("\n\nptr2free  %d , malcounter  %d freedptr %d free index %d \n\n", ptr2free, malcounter, freedptr, freeindex);
      if (ptr2free != 0 && malcounter!=0){
      printf("\n\nhello\n\n");
        free(pointers[freeindex]);
        pointers[freeindex] = NULL;
        ++freeindex;
        ++freedptr;
        ptr2free =malcounter - freedptr;
      }
     // printf("didnt go in free\n");
    }
    if(malcounter == 50){
    break;}
    printf("\n*************  END *********************\n");
    }
  //  if (malcounter == 50){
      while(ptr2free!= 0){
      printf("free left over\n");
        free(pointers[freeindex]);
        pointers[freeindex] = NULL;
        ++freedptr;
        ++freeindex;
        ptr2free= malcounter-freedptr;
      }
   //}
printf("case c done\n");
/*
  //case d
  int memleft=4092;  //the amount of memory left
  int memalloc =0; // the total of memory that is currently allocated
  int* pointers2[50]; // pointer array to all of allocations
  freedptr=0; //amount of pointers that have been freed
  freeindex=0; // index to free at, starts at 0 and frees sequentially. used for pointers2
  malcounter=0; // amount of times malloc has been called
  ptr2free =0; // amount of pointers left to free
  mallocindex=0; // where to store the next mallocd pointer in pointers2
  int memarr[50];// stores the amount of memory mallocd on each malloc
  //int mem;
//  int random = rand()
while(malcounter<=50){
  if (memleft >0){
    random = rand()%2;
    if(random ==0){// malloc if even
      random = rand();
      while(random < 1 || random > 64){
        random = rand();
        if (random <=64 && random >= 1){
          break;
        }
      }
      if(memleft >=random){
        pointers2[mallocindex]= (int*)malloc(random);
        memarr[mallocindex] = random;
        memalloc +=random;
        mallocindex++;
        malcounter++;
        memleft-=random;
      }
    }
    else if (random ==1){//free if odd
      if(ptr2free!=0){
        free(pointers2[freeindex]);
        memalloc = memalloc - memarr[freeindex];
        freeindex++;
        freedptr++;
        ptr2free = malcounter-freedptr;
        memleft = 4092- memalloc;
      }
    }
  }
  if (malcounter ==50){
    break;
  }
}
if(malcounter ==50){
  while(ptr2free>0){
    free(pointers2[freeindex]);
    freeindex++;
    freedptr++;
    ptr2free = malcounter -freedptr;
    if(ptr2free == 0){
      break;
    }
  }
}
printf("case d done\n");
*/
return 0;
}
