#include "mymalloc.h"

void* mymalloc(int size, char *filename, int linenum){
  char* first=&(myMem[0]);
  char* second=&(myMem[1]);
  char* ptr= &(myMem[0]);
  int usrBlock=4092;//size of arr-metadata bits- size of key
  int firstBytes=bin2int(*first, *second);
  if(firstBytes!=KEY){//set key to initialize method
    ptr=bootStrap(ptr, first, second, usrBlock);//set key, initialize first metadata
  
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

}
  return (void*)ptr;
}

void myfree(void *tofree, char *filename, int linenum){
	char* firstmeta = &(myMem[2]);
	tofree = (char*) tofree;
	char* first=&(myMem[0]);//set pointer to first index of arr
	char* second=&(myMem[1]);//set pointer to second byte of arr
	int firstbytes=bin2int(*first, *second);
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
	if((char*)tofree>=(char*)(&(myMem[2])) && (char*)tofree<=(char*)(&(myMem[4095]))){
		char *curr = firstmeta;
		char *prev = NULL;
		char *next = NULL;
		//traversal
		while(curr <= (&(myMem[4095]))){
			char currsizebits = getsizebits(*(curr));
			int currsize = bin2int(currsizebits, *(curr+1));
			
			if ((char*)(curr+2) > (char*)tofree){   // pointer is not pointing at the starting address of a block
				printf("Error in %s line %d: Pointer is not the one given by malloc\n", __FILE__, __LINE__);
				return;
			}
			else if((char*)(curr+2) == tofree){
		
				int isValid = getbit(*(curr), 15); //get inuse bit
			
				if (isValid == 0){  // address already freed
					printf("Error in %s line %d: Pointer is already freed.\n", __FILE__, __LINE__);
					return;
					
				}
				else if (isValid == 1){ //this pointer can be freed
					//free inuse bit, combine block
					setInUse(0, curr);
					// check if curr is the first and last block (only block)
					if ((curr+1+currsize) == (&(myMem[4095])) && prev == NULL){
						setInUse(0, curr);
						return;
					}
					// check if prev is null / curr is first block
					else{
						if (prev == NULL){
							next = (curr+2+currsize);
							combineNext(curr, next);
							return;
						}
						if((curr+1+currsize) == (&(myMem[4095]))){
							combinePrev(curr, prev);
							break;
						}
						else{
							next = (curr+2+currsize);
							combineBoth(prev, curr, next);
							break;
						}
						
					}
				}

			}
			//update pointers
			prev = curr;
			curr = (char*)(curr+2+currsize);
			if ((char*)(curr+2) > (char*)tofree){   // pointer is not pointing at the starting address of a block
				printf("Error in %s line %d: Pointer is not the one given by malloc\n", __FILE__, __LINE__);
				return;
			}

		}
	}
}

char* splitBlock(char* curr, int blockSize, int dataSize){
     char* hi=curr;
     char* lo=curr+1; 
      if((blockSize-3)>dataSize){//if block can fit at least two bytes of free space, including metadata, make free space
         splitBin(dataSize, hi, lo);//set curr's size to the size of data requested (truncating it)
    	 setInUse(1, hi);
          hi=curr+dataSize+2;//iterate our new pointers along
          lo=hi+1;
          blockSize=blockSize-dataSize-2;//blocksize of free block created when you allocate less than space in curr block
          *hi=0;//zero out  garbage vals in these bytes
          *lo=0;
          splitBin(blockSize, hi, lo);//set metadata for new metadata block
          setInUse(0, hi);
      }else{
      	 splitBin(blockSize, hi, lo);
     	 setInUse(1, hi);
      }
      return curr;//curr was never iterated so we can return it as-is
}

void splitBin(unsigned int currInt, char* hiMeta, char* loMeta){
  *hiMeta=0;
  *loMeta=0;
  int i =0;
  unsigned int mask=0;
  unsigned int currBit=0;
  for(i=15; i>=0; i--){
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
    hi=ptr;//set key
    lo=ptr+1;
    splitBin(KEY, hi, lo);
    hi=ptr+2;//initialize metadata after key
    lo=hi+1;
    *hi=0;
    *lo=0;
    splitBin(usrBlock, hi, lo);//set metadata for new metadata block
    setInUse(0, hi);
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
    while(curr>=(&(myMem[2])) && curr<(&(myMem[4095]))){//lowerBound & upperBound will be global vars
      int currMeta=bin2int(*curr, *(curr+1));//converting chars to an int to send to getbit
      int inUse=getbit(currMeta, 15);//getting the in use bit
    
      char hiBits=getsizebits(*curr);//blocking out in use bit to get size of block
      int currBlockSize=bin2int(hiBits, *(curr+1));//getting block size of current block
      if(inUse==0 && currBlockSize>=dataSize){//if there's enough space to return to the user
   
          curr=splitBlock(curr, currBlockSize, dataSize);//prepare it to return
          return curr+2;//return pointer to actual data block, not trying to overwrite metadata
      	  break;
      } 
      else{
          curr=(curr+2+currBlockSize);
      }
    }
    /* got to end of array without finding an empty block */
    printf("Memory request exceeds size of working memory in file %s at line %d\n", __FILE__, __LINE__);
    return NULL;
}

// methods for free: 

int bin2int(char highbyte, char lowbyte){ 
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
	high2 = getsizebits(high22);
	int add2 = bin2int(high1, low11);
	int add1 = bin2int(high2, low22);
	int sum = add2+add1;
	return sum;
}

void combineNext(char* curr, char* next){
	int nextinusebit = getbit(*next, 7);
	if (nextinusebit == 0){
		int sum= bitadd(*curr, *(curr+1) , *next, *(next+1) );
		sum = sum+2; // add next's meta data 
		splitBin(sum, curr, curr+1);
		setInUse(0, curr);
	}
	
}
void combinePrev(char* curr, char* prev){
	int previnusebit = getbit(*prev, 7);
	if (previnusebit == 0){
		int sum= bitadd( *prev, *(prev+1), *curr,*(curr+1));
		sum = sum+2;
		splitBin(sum, prev, prev+1);
		setInUse(0, prev);
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
	}	
}