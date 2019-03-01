myfree(){

}
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
travmeta(){

}
checkptr(){
/*
checks if the pointer given to free is a valid ptr pointing at the start of block
while()
*/


}


int main (int argc, char**argv){

}
