#include <stdio.h>
#include <stdlib.h>
void splitBin(unsigned int currInt, unsigned char* hiMeta, unsigned char* loMeta);
void printBin(unsigned char hi, unsigned char lo);
void printBinInt(unsigned int val);
void setInUse(unsigned int inUse, unsigned char* hiMeta);
int main(int argc, char** argv){
  unsigned int input=2;
  unsigned char hi='0';
  unsigned char lo='0';
printf("begin: \n");
printBin(hi, lo);
  unsigned char* ptrhi=&hi;
  unsigned char* ptrlo=&lo;
  splitBin(input, ptrhi, ptrlo);
  setInUse(1, ptrhi);
  printBin(hi, lo);
  return 0;
}
void setInUse(unsigned int inUse, unsigned char* hiMeta){
    unsigned int mask=1<<7;
    unsigned int currBit=0;
  if(inUse==0){
    *hiMeta|=(*hiMeta & ~mask) | ((currBit << 7) & mask);
  } else if(inUse==1){
        currBit=1<<7;
        *hiMeta|=(*hiMeta & ~mask) | ((currBit << 7) & mask);
  }
    return;
}
/*
use after int arithmetic to save new sum to metadata chars
send in an int, this extracts the bits from it and directly inserts them into the meta data chars using the given high and low byte pointers to the metadata -> int holds 615 (equiv.: 0000001001100111): *hiMeta:00000010 	*loMeta: 01100111
(as of right now it deletes the value in the 'in use' bit when assigning the new val to the chars)
*/
void splitBin(unsigned int currInt, unsigned char* hiMeta, unsigned char* loMeta){
  *hiMeta=0;
  *loMeta=0;
printf("currInt: ");
printBinInt(currInt);
  unsigned int mask=0;
  unsigned int currBit=0;
  for(int i=11; i>=0; i--){
    mask=0;
    currBit=currInt>>i;
    if(i<=7){
        mask=1<<(i);
        *loMeta=(*loMeta & ~mask) | ((currBit << i) & mask);
    } else{
      mask=1<<(i-7);
      *hiMeta=(*hiMeta & ~mask) | ((currBit << i) & mask);
    }

		printf("mask: ");
		printBinInt(mask);
		printf("at %d: ", i);
		printBin(*hiMeta, *loMeta);

  }
    return;
}
void printBin(unsigned char hi, unsigned char lo){
	int shift=0;
	int currBit=0;
	for(int i=15; i>=0; i--){
		if(i>7){
			shift=(i-7);
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
void printBinInt(unsigned int val){
	int shift=0;
	int currBit=0;
	for(int i=31; i>=0; i--){
	shift=i;
	currBit=val>>shift;
	if(currBit & 1){
		printf("1");
		}else{
			printf("0");
			}
	}
		printf("\n");
	return;
}
