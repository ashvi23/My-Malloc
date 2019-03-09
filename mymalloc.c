#include "mymalloc.h"
//#include<stdbool.h>
/*
CONTAINS: getbit, setbit, bin2int, bitadd, bitsub, getsizebits
*/
//int key=11474;
//int ismeminit=0;
//char* firstMallocPtr = &(myMem[4]);
//char* lastaddress = &(myMem[4095]);
//char* upperBound = &(myMem[4095]);
//char* lowerBound = &(myMem[0]);

//int adding(unsigned char, unsigned char, unsigned char, unsigned char);
//int bitsub(unsigned char, unsigned char, unsigned char, unsigned char);


void* mymalloc(int size, char *filename, int linenum){
   printf("###############################################################\n");
  char* first=&(myMem[0]);
  char* second=&(myMem[1]);
  char* ptr= &(myMem[0]);
  int usrBlock=4092;//size of arr-metadata bits- size of key
  int firstBytes=bin2int(*first, *second);
  if(firstBytes!=KEY){//set key to initialize method
    //ismeminit=1;
    ptr=bootStrap(ptr, first, second, usrBlock);//set key, initialize first metadata
    //printf("safe returns from bootstrap\n");
  }
  
  if(size>usrBlock || size<=0){//if user tries to allocate more memory than size of array/metadata/key allows for, or a negative value
      if(size>usrBlock){
      printf("Memory request exceeds size of working memory in file %s at line %d\n", __FILE__, __LINE__);
      return NULL;
    } else{
      printf("Invalid memory request in file %s at line %d\n", __FILE__, __LINE__);
    }
  }else{
    ptr=mallocTraverse(ptr, size);//calling the meat of the program, returns either a pointer to usable memory or a null pointer
  	printf("size being malloced:%d\nMetadata returned from malloc: ", size);
  	//printBin(*(ptr-2), *(ptr-1));
  	//printf("safe returns from malloc traverse\n");
}
  printf("ptr address in malloc: %X\n", ptr);
  
  return (void*)ptr;
}

void myfree(void *tofree, char *filename, int linenum){
	char* firstmeta = &(myMem[2]);
	printf("hello from free:    \n");
	tofree = (char*) tofree;
	char* first=&(myMem[0]);//set pointer to first index of arr
	char* second=&(myMem[1]);//set pointer to second byte of arr
	int firstbytes=bin2int(*first, *second);
	//printf("metadata being freed: ");
	//printBin(*((char*)(tofree)-2), *((char*)(tofree)-1));
	printf("TO FREE ADDRESS: %X \n", (char*)tofree);
	if ((char*)tofree == NULL){
	printf("Error in %s line %d: Pointer received is NULL. \n", __FILE__, __LINE__);
	return;
	}
	if(firstbytes!= KEY){
	printf("Error in %s line %d: Nothing malloc'd yet\n", __FILE__, __LINE__);
	return;
	}
	if((char*)tofree<(char*)(&(myMem[2])) || (char*)tofree>(char*)(&(myMem[4095]))){
	printf("Error in %s line %d: Pointer is not in range of memory\n", __FILE__, __LINE__);
	return;
	}
printf("in free: %X  first: %X  last: %X\n", (char*)tofree,(&(myMem[2])), (&(myMem[4095])));	
	if((char*)tofree>=(char*)(&(myMem[2])) && (char*)tofree<=(char*)(&(myMem[4095]))){

		char *curr = firstmeta;
		char *prev = NULL;
		char *next = NULL;

		while(curr <= (&(myMem[4095]))){
			char currsizebits = getsizebits(*(curr));
			int currsize = bin2int(currsizebits, *(curr+1));
			printf("\n ITERATING:Curr: %X , currsize: %d \n\n", curr, currsize);
			if ((char*)(curr+2) > (char*)tofree){   // pointer is not pointing at the starting address of a block
				printf("Error in %s line %d: Pointer is not the one given by malloc\n", __FILE__, __LINE__);
				break;
			}
			else if((char*)(curr+2) == tofree){
			
printf("INSIDE POINTER EQUALS FREE\n");
				int isValid = getbit(*(curr), 15); //get inuse bit
				printf("In free found address:   ");
				printBin(*curr, *(curr+1));
//break;
printf("isValid: %d\n", isValid);
				if (isValid == 0){  // address already freed
					printf("Error in %s line %d: Pointer is already freed.\n", __FILE__, __LINE__);
					break;
				}
				else if (isValid == 1){ //this pointer can be freed
					//free inuse bit, combine block
					printf("in pointer can be freed\n");
					setInUse(0, curr);
					// check if curr is the first and last block (only block)
					if ((curr+2+currsize) == (&(myMem[4095])) && prev == NULL){
						setInUse(0, curr);
						printf("first and last block\n");
						break;
					}
					// check if prev is null / curr is first block
					else{
						if (prev == NULL){
							printf("PREVIOUS IS NULL\n");
							next = (curr+2+currsize);
							printf("Next Binary:  ");
							printBin(*(next), *(next+1));
							combineNext(curr, next);
							printf("first block \n");
							break;
						}
					// check if curr is the last block / there is no next block
						if((curr+2+currsize) == (&(myMem[4095]))){
							printf("NEXT IS NULL\n");
							combinePrev(curr, prev);
							printf("last block\n");
							break;
						}
					// else combine both
						else{
							printf("PREV NOT NULL && NEXT NOT NULL\n");
							next = (curr+2+currsize);
							printf("prev: %X curr: %X next: %X currsize: %d \n", prev, curr, next, currsize);
							combineBoth(prev, curr, next);
							printf("combined both\n");
							
							break;
						}
						
					}
					//printBin(*curr, *(curr+1));
					//break;
				}

			}
			//update pointers
printBin(*(curr), *(curr+1));
			prev = curr;
printf("Curr before %X  Curr+1:%X   Curr Now: ", curr, curr+1);
			curr = (char*)(curr+2+currsize);
printf("%X    Currsize:%d   \n", curr, currsize);

		}
	}
printf("goodbye from free\n");
printf("\n\n\n\n");
}

char* splitBlock(char* curr, int blockSize, int dataSize){
     char* hi=curr;
     char* lo=curr+1; 
     //printf("in split block:  ");
	//printBin(*(hi), *(lo));
      if((blockSize-3)>dataSize){//if block can fit at least two bytes of free space, including metadata, make free space
         // printf("am i in line 126?\n");
          splitBin(dataSize, hi, lo);//set curr's size to the size of data requested (truncating it)
     	//printf("line 128:    ");
     	//printBin(*(hi), *(lo));
     	setInUse(1, hi);
          hi=curr+dataSize+2;//iterate our new pointers along
          lo=hi+1;
          blockSize=blockSize-dataSize-2;//blocksize of free block created when you allocate less than space in curr block
          *hi=0;//zero out  garbage vals in these bytes
          *lo=0;
         // printf("line 135:    ");
          //printBin(*(hi), *(lo));
          splitBin(blockSize, hi, lo);//set metadata for new metadata block
          setInUse(0, hi);
      }else{
      	 splitBin(dataSize, hi, lo);
     	 setInUse(1, hi);
      }
      return curr;//curr was never iterated so we can return it as-is
}

void splitBin(unsigned int currInt, char* hiMeta, char* loMeta){
  *hiMeta=0;
  *loMeta=0;
  unsigned int mask=0;
  unsigned int currBit=0;
  for(int i=15; i>=0; i--){
    mask=0;
    currBit=currInt>>i;
    if(i<=7){
        mask=1<<(i);
        *loMeta=(*loMeta & ~mask) | ((currBit << i) & mask);
    } else{
      mask=1<<(i-8);
      *hiMeta=(*hiMeta & ~mask) | ((currBit << (i-8)) & mask);
    }
  }
    return;
}
 char* bootStrap(char* ptr, char* hi, char* lo, int usrBlock){
    //printf("bootstrap babeyy\n");
    hi=ptr;//set key
    lo=ptr+1;
    splitBin(KEY, hi, lo);
    hi=ptr+2;//initialize metadata after key
    lo=hi+1;
    *hi=0;
    *lo=0;
    splitBin(usrBlock, hi, lo);//set metadata for new metadata block
    setInUse(0, hi);
    //printf("IN BOOTSTRAP:     \n");
    //printBin(*(hi), *(lo));
    return hi;
}
/*sets the in use bit , takes in an integer (functioning as a boolean), to tell it whether to assign the val to be either 1 or 0*/
void setInUse(int inUse, char* hiMeta){
    unsigned int mask=1<<7;
    unsigned int currBit=0;
  if(inUse==0){
    *hiMeta=(*hiMeta & ~mask) | ((currBit) & mask);
  } else if(inUse==1){
        currBit=1<<7;
        *hiMeta=(*hiMeta & ~mask) | ((currBit) & mask);
  }
    return;
}

char* mallocTraverse(char* curr, int dataSize){
	curr=&(myMem[2]);
    *curr=myMem[2];
	//printf("address of beginning of array: %X\n", &(myMem[0]));
	//printf("address at beginning of traversal: %X\n", curr);
	//printf("curr at begining of traverse: \n");
	//printBin(*(curr),*(curr+1));
    //printf("datasize: %d   \n", dataSize);
    while(curr>=(&(myMem[2])) && curr<(&(myMem[4095]))){//lowerBound & upperBound will be global vars
      int currMeta=bin2int(*curr, *(curr+1));//converting chars to an int to send to getbit
      int inUse=getbit(currMeta, 15);//getting the in use bit
    //  printf("MALLOC TRAV: in use: %d\n", inUse);
      //break;
      char hiBits=getsizebits(*curr);//blocking out in use bit to get size of block
      int currBlockSize=bin2int(hiBits, *(curr+1));//getting block size of current block
      //printf("in use: %d curr block: %d, datasize: %d\n", inUse, currBlockSize, dataSize);
	//  printf("current metadata in traverse: ");
    //  printBin(*(curr),*(curr+1));
      if(inUse==0 && currBlockSize>=dataSize){//if there's enough space to return to the user
      	  printf("currBlockSize: %d\n", currBlockSize);
          curr=splitBlock(curr, currBlockSize, dataSize);//prepare it to return
          return curr+2;//return pointer to actual data block, not trying to overwrite metadata
      	  break;
      } 
      else{
	 // printf("in mallocTraverse: iterating from %X to ", curr);
          curr=(curr+2+currBlockSize);
	  //printf("%X\n", curr);
      }
      //printf("traversing\n");
    }
    /* got to end of array without finding an empty block */
    printf("Memory request exceeds size of working memory in file %s at line %d\n", __FILE__, __LINE__);
    return NULL;
}

int bin2int(char highbyte, char lowbyte){  //WORKS
 	int j =0;
	int i=0;
	char binarr[15];
	  for(i = 7; i>=0; i--){
		binarr[i] = getbit(highbyte, j);\
		j++;
	  }
	  j=0;
	  for(i = 15; i>= 8; i--){
		binarr[i] = getbit(lowbyte, j);
		j++;
	  }
	  //bin arr gives you full binary array ex. byte holds 14 -> binarr = [0,0,0,0,0,0,0,0,1,1,1,0]
	  j = 0;
	  int sum = 0;
	  // this loop goes through binarr and calculate 2^binarr[i] power and sums it to give you the final int. starts at 2^0 (binarr[15])
	  for(i =15; i>=0; i-- ){
		int bin = binarr[i];
		if(bin == 0){
		  j++;
		}
		else if (bin == 1){
		  sum += pow(2, j);
		  j++;
		}
	  }
	  return sum;
}

char getsizebits(char bits){
	char sizebits, mask;
	mask = (1 << 7) -1;
	sizebits = bits & mask;
	return sizebits;
}

int getbit(int num, int position){   //WORKS
	int bitstate = (num >> position) &1;
	return bitstate;
}


int bitadd(unsigned char high11, unsigned char low11, unsigned char high22, unsigned char low22){
	char high1, high2;
	high1 = getsizebits(high11);
	//low1 = getsizebits(low11);
	high2 = getsizebits(high22);
	//low2 = getsizebits(low22);
	int add2 = bin2int(high1, low11);
	int add1 = bin2int(high2, low22);
	int sum = add2+add1;
	return sum;
}
/*
look at notes for bit add, does the same thing. highlevel/lowlevel subfrom should be the bigger number you subtract FROM
bitsub will follow same procedure as bitadd, dont forget to call split in mymalloc()
call method that retrieves the size bits.
 */
int bitsub(unsigned char high11, unsigned char low11, unsigned char high22, unsigned char low22){
	unsigned char high1, high2;
	high1 = getsizebits(high11);
	//low1 = getsizebits(low11);
	high2 = getsizebits(high22);
	//low2 = getsizebits(low22);
	int subfrom = bin2int(high1, low11);
	int tosub = bin2int(high2, low22);
	int sum = subfrom-tosub;
	return sum;
}

/*
MUST SEND IN SIZE BYTES ONLY
this method will NOT take inuse bit into account when converting.
getbit will give you the bit at any given position
send in the lowlevel and high level bits you want to convert into ints, will return the int
*/
void combineNext(char* curr, char* next){
	int nextinusebit = getbit(*next, 7);
	printf("next in use bit: %d\n", nextinusebit);
	if (nextinusebit == 0){
		char currlowbits = *(curr+1);
		char nextlowbits = *(next+1);
		printf("Starting combining process. \n");
		char currhibits=getsizebits(*curr);
	    char nexthibits=getsizebits(*next);
		int currNum=bin2int(currhibits, currlowbits);
		int nextNum=bin2int(nexthibits,nextlowbits);
		printf("currnum: %d \n nextnum: %d\n", currNum, nextNum);
		printf("curr: ");
		printBin(*(curr), *(curr+1));
		printf("next: ");
		printBin(*(next), *(next+1));
		int sum= bitadd(*curr, currlowbits, *next, nextlowbits);
		sum = sum+2; // add next's meta data 
		printf("sum is: %d \n", sum);
		splitBin(sum, curr, curr+1);
		printf("curr new is:  ");
		setInUse(0, curr);
		printBin(*(curr), *(curr+1));
		printf("Curr and Next combined.\n");
		printf("address after combining: %X \n", curr);
		char hibyte=getsizebits(*curr);
		int currsize=bin2int(hibyte, *(curr+1));
		printf("size of combined block: %d\n", currsize);
	}
	else if (nextinusebit ==1){
		printf("Can't Combine. Next is in use.\n");
	}
	
}
void combinePrev(char* curr, char* prev){
	int previnusebit = getbit(*prev, 7);
	if (previnusebit == 0){
		char currlowbits = *(curr+1);
		char prevlowbits = *(prev+1);
		printf("Starting combining process. \n");
		int sum= bitadd( *prev, prevlowbits, *curr, currlowbits);
		sum = sum+2;
		//printf();
		splitBin(sum, prev, prev+1);
		setInUse(0, prev);
		char hibyte=getsizebits(*prev);
		int currsize=bin2int(hibyte, *(prev+1));
		printf("size of combined block: %d\n", currsize);
		printf("Curr and Prev combined.\n");
	}
	else if (previnusebit ==1){
		printf("Can't Combine. Prev is inuse.\n");
	}

}
void combineBoth(char* prev, char* curr, char* next){
	int nextinuse = getbit(*next, 7);
	int previnuse = getbit(*prev, 7);
	if (nextinuse == 0){
	combineNext(curr, next);
	}
	if (previnuse == 0){
	combinePrev(curr, prev);
	int abc = bin2int(*(prev),*(prev+1));
	printf("\n\n FINAL BLOCK:  %d \n\n", abc);
	}
	
	printf("next in use bit: %d  prev in use bit: %d\n" ,nextinuse, previnuse );
	
}
void printBin(char hi, char lo){
	int shift=0;
	int currBit=0;
	for(int i=15; i>=0; i--){
		if(i>7){
			shift=(i-8);
			currBit=hi>>shift;
		} else{
			shift=i;
			currBit=lo>>shift;
			}
	if(currBit & 1){
		printf("1");
		}else{
			printf("0");
			}
	}
		printf("\n");
	return;
}
