#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
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
int* ptrarr2[150];
srand(time(NULL));
int a=0;
int b=0;
int c=0;
int d=0;
int e=0;
int f=0;
int i=0;
struct timeval start, end;

// case a
for(a=0; a<100;a++){
//time(&starttime);//get time at start
gettimeofday(&start, NULL);
for(i=0 ; i< 150; i++){
  ptrarr2[i] = (int*) malloc(1);
  free(ptrarr2[i]);
ptrarr2[i] = NULL;
}
//time(&endtime);//get time at end
gettimeofday(&end, NULL);
difference=((end.tv_sec-start.tv_sec)*1000000)+(end.tv_usec-start.tv_usec);//save runtime of iteration
sumtimeA+=difference;
}
printf("end of case a\n");
//case b
int *ptrarr[50];
int malcounter=0;
int *ptr;
for(b=0; b<100; b++){
gettimeofday(&start, NULL);//get time at start 
int x ;
for(x =0; x<3; x++){
for(i =0; i< 50; i++){
  ptr = (int*) malloc(1);
  ptrarr[i] =ptr;
  malcounter++;
  if(malcounter == 50){
    int j;
    for (j =0; j<malcounter;j++ ){
      free(ptrarr[j]);
      ptrarr[j]=NULL;
  }
  malcounter =0;
}
}
}
gettimeofday(&end, NULL);//get time at end
difference=((end.tv_sec-start.tv_sec)*1000000)+(end.tv_usec-start.tv_usec);//save runtime of iteration
sumtimeB+=difference;
}
printf("end of b\n");
// case c
malcounter = 0;
int freedptr = 0;
int ptr2free =-1;
int freeindex =0;
int* pointers[50];
int mallocindex =0;
int random;
for(c=0; c<100; c++){
gettimeofday(&start, NULL);//get time at start
  while(malcounter <=50){
   random = rand()%2;
    if(random == 0){ //malloc if 0
      pointers[mallocindex] = (int*)malloc(1);
      malcounter++;
      mallocindex++;
      ptr2free =malcounter - freedptr;
    }
    else if (random == 1){ // free if 1
      if (ptr2free != 0 && malcounter!=0){
        free(pointers[freeindex]);
        pointers[freeindex] = NULL;
        ++freeindex;
        ++freedptr;
        ptr2free =malcounter - freedptr;
      }
    }
    if(malcounter == 50){
    break;
  }
   
    }
  //  if (malcounter == 50){
      while(ptr2free!= 0){
        free(pointers[freeindex]);
        pointers[freeindex] = NULL;
        ++freedptr;
        ++freeindex;
        ptr2free= malcounter-freedptr;
      }
   //}
gettimeofday(&end, NULL);//get time at end
difference=((end.tv_sec-start.tv_sec)*1000000)+(end.tv_usec-start.tv_usec);//save runtime of iteration
sumtimeC+=difference;
}
printf("end of c\n");
  //case d
  int memleft=4092;  //the amount of memory left
  int memalloc =0; // the total of memory that is currently allocated
  int* pointers2[50]; // pointer array to all of allocations
  int memarr[50];// stores the amount of memory mallocd on each malloc

for(d=0; d<100; d++){
	gettimeofday(&start, NULL);//get time at start
	  memleft=4092;
	  freedptr=0; //amount of pointers that have been freed
	  freeindex=0; // index to free at, starts at 0 and frees sequentially. used for pointers2
	  malcounter=0; // amount of times malloc has been called
	  ptr2free =-1; // amount of pointers left to free
	  mallocindex=0; // where to store the next mallocd pointer in pointers2
	while(malcounter<=50){
	 if (memleft >0){
	    random = rand()%2;
	    if(random ==0){// malloc if even
	      random = (rand()%64);
		if(random==0){
			random=64;
		}
	      /*while(random < 1 || random > 64){
		random = rand();
		if (random <=64 && random >= 1){
		  break;
		}
	      }*/
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
	      if(ptr2free!=0&& malcounter!=0){
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
	//if(malcounter ==50){
	  while(freeindex <=50){
	    free(pointers2[freeindex]);
	    freedptr++;
	    ptr2free = malcounter -freedptr;
	    memalloc = memalloc - memarr[freeindex];
	    freeindex++;
	    memleft = 4092- memalloc;
	    
	    if(ptr2free == 0){
	      break;
	    }
	   }

	gettimeofday(&end, NULL);//get time at end
	difference=((end.tv_sec-start.tv_sec)*1000000)+(end.tv_usec-start.tv_usec);//save runtime of iteration
	sumtimeD+=difference;
}
printf("end of d\n");
int *fiboptrArr[100];
int index=0;//used in E and F
int sum=0;//used in E and F
for(e=0; e<100; e++){
	gettimeofday(&start, NULL);//get time at start
	int prevprev=0;
	int prev=1;
	int totalmem=0;
	index=0;
	//case E
	while(totalmem<(4092/2)){
	  sum=prevprev+prev;
	  fiboptrArr[index]= (int*)malloc(sum);
	  prevprev=prev;
	  prev=sum;
	  totalmem+=(sum+2);
	  index++;
	}
	  fiboptrArr[index]= (int*)malloc(prevprev);
	  totalmem+=(prevprev+2);
	  index++;
	while(totalmem+(prev-prevprev)<(4092)&& sum>1){
	  sum=prev-prevprev;
	  fiboptrArr[index]= (int*)malloc(sum);
	  prev=prevprev;
	  prevprev=sum;
	  totalmem+=(sum+2);
	  index++;
	}
	for(i=index-1; i>=0; i--){
	  free(fiboptrArr[i]);
	}
	gettimeofday(&end, NULL);//get time at end
	difference=((end.tv_sec-start.tv_sec)*1000000)+(end.tv_usec-start.tv_usec);//save runtime of iteration
	sumtimeD+=difference;
}
printf("end of e\n");
//F begins here
int* alternptrArr[250];
int* alternptr;
for(f=0; f<100; f++){
	gettimeofday(&start, NULL);//get time at start
	index=0;
	random=0;
	while(sum<=4092 && index<250){
		random=rand()%67;
		if(random==0){
			random=67;
		}
		alternptr=(int*)malloc(random);
		alternptrArr[index]=alternptr;
		if((index%3)==0){
			free(alternptrArr[index]);//every third element gets freed
			alternptrArr[index]=NULL;
			}
		index++;
		sum+=random+2;
	}
	for(i=0; i<index; i++){
	
		if(alternptrArr[i]!=NULL){
		free((alternptrArr[i]));
		}}
	gettimeofday(&end, NULL);//get time at end
	difference=((end.tv_sec-start.tv_sec)*1000000)+(end.tv_usec-start.tv_usec);//save runtime of iteration
	sumtimeD+=difference;
	//Check for successful freeing
	char* testptr;
	char* testptrArr[4];
	//malloc 1000 4X
	for(i=0; i<4; i++){
		testptr=(char*)malloc(1000);
		testptrArr[i]=testptr;
	}
	//free prev mallocs
	for(i=0; i<4; i++){
		free((testptrArr[i]));
	}
	//test to see how this worked
	testptr=(char*)malloc(4092);
	testptrArr[0]=testptr;
	free((testptrArr[0]));
	//test our free
	testptr=(char*)malloc(1);
	testptrArr[0]=testptr;
	free((testptrArr[0]));
	//test splitblock
	testptr=(char*)malloc(4088);
	testptrArr[0]=testptr;
	testptr=(char*)malloc(1);
	testptrArr[1]=testptr;
	free((testptrArr[1]));
	free((testptrArr[0]));
	testptr=(char*)malloc(4092);
	testptrArr[0]=testptr;
	free((testptrArr[0]));
}
printf("end of f\n");




//print mean times
printf("Mean time of protocol A was %lf milliseconds\n", (sumtimeA/100));
printf("Mean time of protocol B was %lf milliseconds\n", (sumtimeB/100));
printf("Mean time of protocol C was %lf milliseconds\n", (sumtimeC/100));
printf("Mean time of protocol D was %lf milliseconds\n", (sumtimeD/100));
printf("Mean time of protocol E was %lf milliseconds\n", (sumtimeE/100));
printf("Mean time of protocol F was %lf milliseconds\n", (sumtimeF/100));
return 0;
}
