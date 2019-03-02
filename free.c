char* firstmeta = mem[2];
char* firstMallocPtr = mem[4];
char*lastaddress = mem[4095];
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

/*
in main:
//key = 11474
unsigned char lowbits = *(curr-1);
unsigned char highbits = *(curr -2);
int checkKey = bin2int(highbits, lowbits);

if (checkKey == 11474){
	combineRight(curr, curr+1+currsize);
}




*/


/*
  - prev = inuse curr next = inuse
  - prev = !inuse curr next = inuse
  - prev = !inuse curr next = !inuse
  - prev = inuse curr next = !inuse

  check left
  if prev = free
  extract 16-1 rightmost bits (the size bits) on curr
  bin2int size bits on curr
  extract size bits from prev
  bin2int size bits on prev
  bitadd prevsize curr size
  int2bin sum
  change prev ptr size to sum bits
  set char ptr curr in use bit to 0

  check right
  if prev! freeblocks
  check if curr + metadata at(currsize + sizeof(metadata)) is free
  extract 16-1 rightmost bits (the size bits) on curr
  bin2int size bits on curr
  extract size bits from prev
  bin2int size bits on prev
  bitadd prevsize curr size
  int2bin sum
  change prev ptr size to sum bits
  set char ptr curr in use bit to 0

  if left in use and right in Use
    do nothing. there is nothing to combine.

  */
}
unsigned char* travfree(unsigned char* curr, unsigned char* prev, ){

}

/*
unsigned char* mallocTraverse(unsigned char* curr, int dataSize){
    *curr=myMem[2];
    while(curr>=lowerBound && curr<=upperbound){//lowerBound & upperBound will be global vars
      int currMeta=bin2int(*curr, *(curr+1));
      int inUse=getbit(currMeta, 15);//hopefully this works
      char hiBits=getsizeBits(*curr);//blocking out in use bit
      int currBlockSize=(hiBits, *(curr+1));//getting block size of current block
      if(inUse==0 && currBlockSize>=dataSize){
            //call split fxn
      } else{
          curr=(curr+currBlockSize);
      }
    }
    printf("Memory full\n");
    return NULL;
}

*/
checkptr(){
/*
checks if the pointer given to free is a valid ptr pointing at the start of block
while()
*/


}

void myfree(void *tofree, char*file, int*linenum){
	tofree = (char*) tofree;
	if (tofree == NULL){
	printf("Error in %s line %d: Pointer received is NULL. \n", file, linenum);
	}
	if (ismeminit = 0){
	printf("Error in %s line %d: Nothing malloc'd yet\n", file, linenum);
	}
	if(tofree<=lowerBound || tofree>upperbound){
	printf("Error in %s line %d: Pointer is not in range of memory\n", file, linenum);
	}
	if(tofree>firstmeta && tofree<=lastaddress){

		char *curr = firstmeta;
		char *prev = NULL;
		char *next = NULL:

		while(curr < lastaddress ){
			if ((curr+2) > tofree){   // pointer is not pointing at the starting address of a block
				printf("Error in %s line %d: Pointer is not the one given by malloc\n", file, linenum);
				break;
			}
			if(curr+2 == tofree){
				int isValid = getbit(curr, 1); //get inuse bit
				if (isValid == 0){  // address already freed
					printf("Error in %s line %d: Pointer is already freed.\n", file, linenum);
					break;
				}
				else if (isValid == 1){ //this pointer can be freed
					//free inuse bit, combine block
					setInUse(0, curr);
					// check if curr is the first and last block (only block)
					unsigned char currsizebits = getsize(curr);
					int currsize = bin2int(currsizebits, curr+1);

					// check if prev is null / curr is first block
					if (prev == NULL){

						combineRight(&curr, )
					}
					// check if curr is the last block / there is no next block
					// else combine both


					break;
				}

			}
			//update pointers
		}
	}

}
int main (int argc, char**argv){


}
