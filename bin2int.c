#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include<stdbool.h>

int bin2int(unsigned char, unsigned char);
int getbit(int , int);
//int adding(unsigned char, unsigned char, unsigned char, unsigned char);
//int bitsub(unsigned char, unsigned char, unsigned char, unsigned char);
unsigned char getsizebits(bits);

//send in the whole byte. returns size bits.
unsigned char getsizebits(unsigned char bits){
	unsigned char sizebits, mask;
	mask = (1 << 15) -1;
	sizebits = bits & mask;
	return sizebits;
}

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

int getbit(int num, int position){   //WORKS
	int bitstate = (num >> position) &1;
	return bitstate;
}

/*
MUST SEND IN SIZE BYTES ONLY
this method will NOT take inuse bit into account when converting.
getbit will give you the bit at any given position
send in the lowlevel and high level bits you want to convert into ints, will return the int
*/
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
