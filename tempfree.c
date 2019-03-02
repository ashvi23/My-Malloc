#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include<stdbool.h>
#define KEY 0010110011010010
/*
CONTAINS: getbit, setbit, bin2int, bitadd, bitsub, getsizebits
*/
char* firstmeta = mem[2];
char* firstMallocPtr = mem[4];
char*lastaddress = mem[4095];

int bin2int(unsigned char, unsigned char);
int getbit(int , int);
//int adding(unsigned char, unsigned char, unsigned char, unsigned char);
//int bitsub(unsigned char, unsigned char, unsigned char, unsigned char);
unsigned char getsizebits(bits);

/*
send in high and low bytes for the meta data you want to add TO   (highleva2, lowleva2)   send in metadata bytes for the meta data you have to add (the one youre gonna free)
bit add will call a method to retreive the size bits from the whole bytes and then send that to bin2int and then add+return the resulting ints' sum
*/
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
	if(tofree<=lowerBound || tofree>upperbound){
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

int main (int argc, char**argv){
	unsigned char high= 0b0000001;
	unsigned char low = 0b00001111;
	int f = bin2int(high, low);
	printf("INT : %d", f);
	unsigned char high2= 0b0000000;
	unsigned char low2 = 0b00001111;
	int added = bitadd(high, low, high2, low2);
	printf("sum : %d \n", added);
	int subtracted = bitsub(high, low, high2, low2);
	printf("subtracted : %d\n", subtracted);
	return 0;
}
