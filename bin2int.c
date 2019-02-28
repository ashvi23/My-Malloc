#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include<stdbool.h>

int bin2int(unsigned char, unsigned char);
int getbit(int , int);


int getbit(int num, int position){   //WORKS
	int bitstate = (num >> position) &1;
	return bitstate;
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


int main (int argc, char**argv){
	unsigned char high= 0b10000000;
	unsigned char low = 0b00001111;
	int f = bin2int(high, low);
	printf("INT : %d", f);
	return 0;
}
