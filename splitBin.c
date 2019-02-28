#include <stdio.h>
#include <stdlib.h>
void splitBin(unsigned int currInt, unsigned char* hiMeta, unsigned char* loMeta);
void printBin(unsigned char hi, unsigned char lo);
void printBinInt(unsigned int val);
int main(int argc, char** argv){
  unsigned int input=2;
  unsigned char hi='0';
  unsigned char lo='0';
printf("begin: \n");
printBin(hi, lo);
  unsigned char* ptrhi=&hi;
  unsigned char* ptrlo=&lo;
  splitBin(input, ptrhi, ptrlo);
  printBin(hi, lo);
  return 0;
}

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
