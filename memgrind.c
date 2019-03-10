#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.c"
#include "mymalloc.h"
#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)

int main (int argc, char**argv){
time_t starttime;
time_t endtime;
double difference=0;
double sumtimeA=0;
double sumtimeB=0;
double sumtimeC=0;
double sumtimeD=0;
double sumtimeE=0;
double sumtimeF=0;
//int*ptrarr2[150];
// case a
/*time(&starttime);//get time at start
for(int i =0 ; i< 150; i++){
printf("inside case a\n");
  ptrarr2[i] = (int*) malloc(1);
  free(ptrarr2[i]);
ptrarr2[i] = NULL;
}
time(&endtime);//get time at end
difference=difftime(endtime, starttime);//save runtime of iteration
sumtimeA+=difference;
printf("case a done\n");
//case b*/
int *ptrarr[50];
int malcounter=0;
int *ptr;
time(&starttime);//get time at start
for(int x =0; x<3; x++){
for(int i =0; i< 50; i++){
	ptr = (int*) malloc(1);
	ptrarr[i] =ptr;
	malcounter++;
	if(malcounter == 50){
		for (int j =0; j<malcounter;j++ ){
		 	free(ptrarr[j]);
			ptrarr[j]=NULL;
	}
	malcounter =0;
}
}
}
time(&endtime);//get time at end
difference=difftime(endtime, starttime);//save runtime of iteration
sumtimeB+=difference;
printf("case b done\n");

/*/ case c
int malcounter = 0;
int freedptr = 0;
int ptr2free =-1;
int freeindex =0;
int* pointers[50];
int mallocindex =0;
  int random;
 srand(time(NULL));
time(&starttime);//get time at start
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
      printf("free left\n");
        free(pointers[freeindex]);
        pointers[freeindex] = NULL;
        ++freedptr;
        ++freeindex;
        ptr2free= malcounter-freedptr;
      }
   //}
time(&endtime);//get time at end
difference=difftime(endtime, starttime);//save runtime of iteration
sumtimeC+=difference;
printf("case c done\n");


  //case d
  int memleft=4092;  //the amount of memory left
  int memalloc =0; // the total of memory that is currently allocated
  int* pointers2[50]; // pointer array to all of allocations
  freedptr=0; //amount of pointers that have been freed
  freeindex=0; // index to free at, starts at 0 and frees sequentially. used for pointers2
  malcounter=0; // amount of times malloc has been called
  ptr2free =-1; // amount of pointers left to free
  mallocindex=0; // where to store the next mallocd pointer in pointers2
  int memarr[50];// stores the amount of memory mallocd on each malloc
  //int mem;
//  int random = rand()
time(&starttime);//get time at start
while(malcounter<=50){
 printf("\n\n*************  START  *********************\n\n");
printf("STARTING:  memleftt: %d  memalloc: %d freedptr: %d malcounter: %d ptr2free: %d freeindex: %d mallocindex: %d \n", memleft, memalloc, freedptr, malcounter, ptr2free, freeindex, mallocindex);
  if (memleft >0){
    random = rand()%2;
    printf("\nrandom: %d\n", random);
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
       // ptr2free = malcounter-freedptr;
      }
    }
    else if (random ==1){//free if odd
      if(ptr2free!=0&& malcounter!=0){
        free(pointers2[freeindex]);
        memalloc = memalloc - memarr[freeindex];
        freeindex++;
        freedptr++;
        ptr2free = malcounter-freedptr;
        memleft = 4092- memalloc;
        printf("STARTING:  memleftt: %d  memalloc: %d freedptr: %d malcounter: %d ptr2free: %d freeindex: %d mallocindex: %d \n", memleft, memalloc, freedptr, malcounter, ptr2free, freeindex, mallocindex);
      }
    }
    printf("ENDING:  memleftt: %d  memalloc: %d freedptr: %d malcounter: %d ptr2free: %d freeindex: %d mallocindex: %d \n", memleft, memalloc, freedptr, malcounter, ptr2free, freeindex, mallocindex);
    
    printf("\n\n*************  END *********************\n");
  }
  if (malcounter ==50){
    break;
  }
}
//if(malcounter ==50){
  while(freeindex <=50){
  printf("IN OUTSIDE\n");
  	 printf("pointers: %X    ", pointers2[freeindex]);
    free(pointers2[freeindex]);
    freedptr++;
    ptr2free = malcounter -freedptr;
    //printf("memarray: %d \n", memarr[freeindex]);
    memalloc = memalloc - memarr[freeindex];
    freeindex++;
    memleft = 4092- memalloc;
    
    if(ptr2free == 0){
      break;
    }
    printf("ENDING free:  memleftt: %d  memalloc: %d freedptr: %d malcounter: %d ptr2free: %d freeindex: %d mallocindex: %d \n", memleft, memalloc, freedptr, malcounter, ptr2free, freeindex, mallocindex);
 	}
//}
printf("ENDING:  memleftt: %d  memalloc: %d freedptr: %d malcounter: %d ptr2free: %d freeindex: %d mallocindex: %d \n", memleft, memalloc, freedptr, malcounter, ptr2free, freeindex, mallocindex);
time(&endtime);//get time at end
difference=difftime(endtime, starttime);//save runtime of iteration
sumtimeD+=difference;
printf("case d done\n");








int *fiboptrArr[100];
int prevprev=0;
int prev=1;
int sum=0;
int totalmem=0;
int index=0;
//case E
while(totalmem<(4092/2)){
	sum=prevprev+prev;
	fiboptrArr[index]= (int*)malloc(sum);
	printf("at index %d in memgrind\n sum= %d  totalmem: %d\n", index, sum, totalmem);
	prevprev=prev;
	prev=sum;
	totalmem+=(sum+2);
	index++;
}
	fiboptrArr[index]= (int*)malloc(prevprev);
	totalmem+=(prevprev+2);
	printf("at index %d in memgrind\n sum= %d  totalmem: %d\n", index, sum, totalmem);
	index++;
while(totalmem+(prev-prevprev)<(4092)&& sum>1){
	sum=prev-prevprev;
	fiboptrArr[index]= (int*)malloc(sum);
	printf("at index %d in memgrind\n sum= %d  totalmem: %d\n", index, sum, totalmem);
	prev=prevprev;
	prevprev=sum;
	totalmem+=(sum+2);
	index++;
}
for(int i=index-1; i>=0; i--){
	printf("in E at index %d\n", i);
	free(fiboptrArr[i]);
}
	//fiboptrArr[0]=malloc(4092);
	//fiboptrArr[1]=malloc(1);
	//free(fiboptrArr[0]);
//end of E
//begin of F
	//srand(time(0));
	int* alternptrArr[250];
	index=0;
	random=0;
	while(sum<=4092 && index<250){
		if((index/4)==0){
			//printf("in F\n");
			free(alternptrArr[index-1]);//every third element gets freed
			alternptrArr[index-1]=NULL;
			}
		random=abs(rand()%64);
		printf("CURRENT SUM %d\n", sum);
		alternptrArr[index]=(int*)malloc(random);
		index++;
		sum+=random+2;
	}
	for(int i=0; i<250; i++){
	
		if(alternptrArr[i]!=NULL){
		printf("FREEING PTRARRAY AT INDEX %d\n", i);
		free((alternptrArr[i]));
		}
	}*/
printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  END OF F &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
//print mean times
//printf("Mean time of protocol A was %lf\n", (sumtimeA/100));
printf("Mean time of protocol B was %lf\n", (sumtimeB/100));
//printf("Mean time of protocol C was %lf\n", (sumtimeC/100));
//printf("Mean time of protocol D was %lf\n", (sumtimeD/100));
//printf("Mean time of protocol E was %lf\n", (sumtimeE/100));
//printf("Mean time of protocol F was %lf\n", (sumtimeF/100));
return 0;
}
