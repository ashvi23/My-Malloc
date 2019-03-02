#include "mymalloc.h"
//#include<stdbool.h>
/*
CONTAINS: getbit, setbit, bin2int, bitadd, bitsub, getsizebits
*/
char* firstmeta = myMem[2];
char* firstMallocPtr = myMem[4];
char* lastaddress = myMem[4095];
char* upperBound = myMem[4095];
char* lowerBound = myMem[0];
int ismeminit =0;
//int adding(unsigned char, unsigned char, unsigned char, unsigned char);
//int bitsub(unsigned char, unsigned char, unsigned char, unsigned char);
int bitadd(unsigned char high11, unsigned char low11, unsigned char high22, unsigned low22);
int bitsub(unsigned char high11, unsigned char low11, unsigned char high22, unsigned low22);
void combineBoth(unsigned char* prev, unsigned char* curr, unsigned char* next);
void combineNext(unsigned char* curr, unsigned char* next);
void combinePrev(unsigned char* curr, unsigned char* prev);
void myfree(void *tofree, char*file, int*linenum);
unsigned char getsizebits(bits);
int getbit(int num, int position);
unsigned char getsizebits(unsigned char bits);
int bin2int(unsigned char highbyte, unsigned char lowbyte);
unsigned char* mallocTraverse(unsigned char* curr, int dataSize);
void setInUse(int inUse, unsigned char* hiMeta);
void splitBin(unsigned int currInt, unsigned char* hiMeta, unsigned char* loMeta);
unsigned char* splitBlock(unsigned char* curr, int blockSize, int dataSize);
void* mymalloc(int size, __FILE__, __LINE__);

void* mymalloc(int size, __FILE__, __LINE__){
  unsigned char* first=myMem[0];
  unsigned char* second=myMem[1];
  unsigned char* ptr= myMem[0];
  int firstBytes=bit2int(*first, *second);
  if(firstBytes!=key){//set key to initialize method
    int usrBlock=4092;//size of arr-metadata bits- size of key
    *ptr=key;
    ptr=ptr+2;
    first=ptr;//initialize metadata after key
    second=ptr+1;
    *first=0;
    *second=0;
    splitBin(usrBlock, first, second);//set metadata for new metadata block
    setBlock(0, *hi);
    ismeminit =1;
  }
  if(size>usrBlock || size<0){//if user tries to allocate more memory than size of array/metadata/key allows for, or a negative value
      if(size>usrBlock){
      printf("Memory request exceeds size of working memory in file %d at line %d\n", __FILE__, __LINE__);
      return NULL;
    } else{
      printf("Invalid memory request in file %d at line %d\n", __FILE__, __LINE__);
    }
  }else{
    ptr=mallocTraverse(ptr, size);//calling the meat of the program, returns either a pointer to usable memory or a null pointer
  }
  return (void*)ptr;
}

unsigned char* splitBlock(unsigned char* curr, int blockSize, int dataSize){
     unsigned char* hi=curr;
     unsigned char* lo=curr+1;
     setBlock(1, *hi);
      if((blockSize-3)>dataSize){//if block can fit at least two bytes of free space, including metadata, make free space
          splitBin(dataSize, hi, lo);//set curr's size to the size of data requested (truncating it)
          hi=curr+dataSize+2;//iterate our new pointers along
          lo=hi+1;
          blockSize=blockSize-dataSize-2;//blocksize of free block created when you allocate less than space in curr block
          *hi=0;//zero out  garbage vals in these bytes
          *lo=0;
          splitBin(blockSize, hi, lo);//set metadata for new metadata block
          setBlock(0, *hi);
      }
      return curr;//curr was never iterated so we can return it as-is
}

void splitBin(unsigned int currInt, unsigned char* hiMeta, unsigned char* loMeta){
  *hiMeta=0;
  *loMeta=0;
  unsigned int mask=0;
  unsigned int currBit=0;
  for(int i=11; i>=0; i--){
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

/*sets the in use bit , takes in an integer (functioning as a boolean), to tell it whether to assign the val to be either 1 or 0*/
void setInUse(int inUse, unsigned char* hiMeta){
    unsigned int mask=1<<7;
    unsigned int currBit=0;
  if(inUse==0){
    *hiMeta=(*hiMeta & ~mask) | ((currBit) & mask);
  } else if(inUse==1){
        currBit=1<<7;
	unsigned int combo=(*hiMeta & ~mask);
        *hiMeta=(*hiMeta & ~mask) | ((currBit) & mask);
  }
    return;
}

unsigned char* mallocTraverse(unsigned char* curr, int dataSize){
    *curr=myMem[2];
    while(curr>=lowerBound && curr<=upperbound){//lowerBound & upperBound will be global vars
      int currMeta=bin2int(*curr, *(curr+1));//converting chars to an int to send to getbit
      int inUse=getbit(currMeta, 1);//getting the in use bit
      char hiBits=getsizeBits(*curr);//blocking out in use bit to get size of block
      int currBlockSize=bin2int(hiBits, *(curr+1));//getting block size of current block
      if(inUse==0 && currBlockSize>=dataSize){//if there's enough space to return to the user
          curr=splitBlock(curr, currBlockSize, dataSize);//prepare it to return
          return curr+2;//return pointer to actual data block, not trying to overwrite metadata
      } else{
          curr=(curr+currBlockSize);
      }
    }
    /* got to end of array without finding an empty block */
    printf("Memory request exceeds size of working memory in file %d at line %d\n", __FILE__, __LINE__);
    return NULL;
}

int bin2int(unsigned char highbyte, unsigned char lowbyte){  //WORKS
 	int j =0;
	int i=0;
	char binarr[15];
	  for(i = 7; i>=0; i--){
		binarr[i] = getbit(highbyte, j);
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

unsigned char getsizebits(unsigned char bits){
	unsigned char sizebits, mask;
	mask = (1 << 7) -1;
	sizebits = bits & mask;
	return sizebits;
}

int getbit(int num, int position){   //WORKS
	int bitstate = (num >> position) &1;
	return bitstate;
}


int bitadd(unsigned char high11, unsigned char low11, unsigned char high22, unsigned low22){
	unsigned char, high1, high2;
	high1 = getsize(high11);
	//low1 = getsize(low11);
	high2 = getsize(high22);
	//low2 = getsize(low22);
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
int bitsub(unsigned char high11, unsigned char low11, unsigned char high22, unsigned low22){
	unsigned char, high1, high2;
	high1 = getsize(high11);
	//low1 = getsize(low11);
	high2 = getsize(high22);
	//low2 = getsize(low22);
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
void combineNext(unsigned char* curr, unsigned char* next){
	int nextinusebit = getbit(*next, 1);
	if (nextinusebit == 0){
		unsigned char currlowbits = *(curr+1);
		unsigned char nextlowbits = *(next+1);
		printf("Starting combining process. \n");
		int sum= bitadd(*curr, currlowbits, *next, nextlowbits);
		splitBin(sum, curr, curr+1);
		setInUse(0, curr);
		printf("Curr and Next combined.\n");
	}
	else if (nextinusebit ==1){
		printf("Can't Combine. Next is in use.\n");
	}
}
void combinePrev(unsigned char* curr, unsigned char* prev){
	int previnusebit = getbit(*prev, 1);
	if (previnusebit == 0){
		unsigned char currlowbits = *(curr+1);
		unsigned char prevlowbits = *(prev+1);
		printf("Starting combining process. \n");
		int sum= bitadd( *prev, prevlowbits, *curr, currlowbits);
		splitBin(sum, curr, curr+1);
		setInUse(0, prev);
		printf("Curr and Prev combined.\n");
	}
	else if (previnusebit ==1){
		printf("Can't Combine. Next is in use.\n");
	}
}
void combineBoth(unsigned char* prev, unsigned char* curr, unsigned char* next){
	int nextinuse = getbit(*next, 1);
	int previnuse = getbit(*prev, 1);
	if (nextinuse == 0){
	combineNext(curr, next);
	}
	if (previnuse == 0){
	combinePrev(curr, prev);
	}
}
void myfree(void *tofree, __FILE__, __LINE__){
	tofree = (char*) tofree;
	if (tofree == NULL){
	printf("Error in %s line %d: Pointer received is NULL. \n", __FILE__, __LINE__);
	}
	if (ismeminit = 0){
	printf("Error in %s line %d: Nothing malloc'd yet\n", file, linenum);
	}
	if(tofree<=lowerBound || tofree>upperBound){
	printf("Error in %s line %d: Pointer is not in range of memory\n", __FILE__, __LINE__);
	}
	if(tofree>firstmeta && tofree<=lastaddress){

		char *curr = firstmeta;
		char *prev = NULL;
		char *next = NULL;

		while(curr < lastaddress ){
			unsigned char currsizebits = getsize(curr);
			int currsize = bin2int(currsizebits, curr+1);

			if ((curr+2) > tofree){   // pointer is not pointing at the starting address of a block
				printf("Error in %s line %d: Pointer is not the one given by malloc\n", __FILE__, __LINE__);
				break;
			}
			if(curr+2 == tofree){
				int isValid = getbit(curr, 1); //get inuse bit
				if (isValid == 0){  // address already freed
					printf("Error in %s line %d: Pointer is already freed.\n", __FILE__, __LINE__);
					break;
				}
				else if (isValid == 1){ //this pointer can be freed
					//free inuse bit, combine block
					setInUse(0, curr);
					// check if curr is the first and last block (only block)
					if ((curr+1+currsize) == lastaddress && prev == NULL){
						setInUse(0, curr);
						break;
					}
					// check if prev is null / curr is first block
					else{
						if (prev == NULL){
							next = (curr+1+currsize);
							combineNext(curr, next);
							break;
						}
					// check if curr is the last block / there is no next block
						if((curr+1+currsize) == lastaddress){
							combinePrev(curr, prev);
							break;
						}
					// else combine both
						else if((curr+1+currsize) < lastaddress && prev!=NULL){
							next = (curr+1+currsize);
							combineBoth(prev, curr, next);
							break;
						}
					}
					//break;
				}

			}
			//update pointers

			prev = curr;
			curr = curr+1+currsize;
		}
	}

}
