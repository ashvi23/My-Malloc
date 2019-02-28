#include <math.h>
#include <stdbool.h>
#define KEY 0010110011010010

bitadd(unsigned char highleva2, unsigned char lowleva2, unsigned char highlevl2add, unsigned char lowlev2add){
  //call bin2int twice. save those numbers. add ints. call int2binary. call split
    int add2int =  bin2int(unsigned char lowleva2, unsigned char highleva2);
    int toadd =  bin2int(unsigned char lowlev2a, unsigned char highlev2a);
    int newsize = add2int+toadd;
    char[] newbinary = int2binary(newsize);
    return newbinary;
//myfree will receive the full 16 bit char array, then call split on the array from within myfree()
}
bitsub(unsigned char highlevsubfrom, unsigned char lowlevsubfrom, unsigned char highlevl2sub, unsigned char lowlev2sub){
  //bitsub will follow same procedure as bitadd, dont forget to call split in mymalloc()
  int sub =  bin2int(unsigned char lowlevsubfrom, unsigned char highlevsubfrom);
  int tosub =  bin2int(unsigned char lowlev2sub, unsigned char highlev2sub);
  int newsize = sub - tosub;
  char[] newbinary = int2binary(newsize);
  return newbinary;

}
//converts binary to int
bool getBit(unsigned char byte, int position) // position in range 0-7
{
    //copied code MODIFY
    return (byte >> position) & 0x1;
}
//getbit will give you the bit at any given position
int bin2int(unsigned char lowlev, unsigned char highlev){
int j =0;
  for(int i = 0; i< 8; i++){
    binarr[i] = getbit(highlev, j);
    j++;
  }
  j=0;
  for(int i = 8; i< 16; i++){
    binarr[i] = getbit(lowlev, j);
    j++;
  }
  ///bin arr gives you full binary array ex. byte holds 14 -> binarr = [0,0,0,0,0,0,0,0,1,1,1,0]
  int j = 0;
  int sum = 0;
  // this loop goes through binarr and calculate 2^binarr[i] power and sums it to give you the final int. starts at 2^0 (binarr[15])
  for(int i =15; i>=0; i-- ){
    int bin = binarr[i]
    if (bin == 0){
      j++;
    }
    else if (bin == 1){
      sum += pow(2, j);
      j++;
    }
  }
  return sum;
}
char* int2binary(int toconvert){
  static char binum[16]; //idk if this works figure out types later, conversion code should work tho
  //do i need to null terminate? is this a string or a array of characters?
  int i =0;
  for (i = 0; i < 16; i++){
    binum[i]=0;
  }
  i =0;
  while(num>0){
    binum[i] = num%2;
    num = num/2;
    i++;
  }
  //now binum contains reversed binary numbers
  //this loop makes the numbers forward again
  int start = 0;
  int end = 15;
  while(start < end){
    int temp = binum[start];
    binum[start] = binum[end];
    binum[end]= temp;
    start++;
    end--;
  }
  char finbin[16];
  for(int i =0; i<16; i++){
    finbin[i] = binum[i];
  }
}
unsgined char splitbinary(char* tosplit, int split){
  //split = 1 means high split aka obtain the high level bits
  // split == 0 means low split aka obtain the low level bits
  //https://stackoverflow.com/questions/2666440/how-to-store-binary-string-in-the-binary-form-in-a-file
  if (split ==1){

  }

  else if (split ==0){
  }
}
//unsgined char lowsplitbinary(char* tosplit){}
/*
http://www.java2s.com/Code/Java/Language-Basics/Setsaspecificbitofanint.htm
MUST MODIFY
public static int setBit(int bit, int target) {
       // Create mask
       int mask = 1 << bit;
       // Set bit
       return target | mask;
    }

*/

//following for setting bit is from geeksforgeeks MUST MODIFY!
//Use the bitwise OR operator (|) to set a bit.
//number |= 1UL << n;
//That will set the nth bit of number. n should be zero, if you want to set the 1st bit and so on upto n-1,
//if you want to set the nth bit.
//Use 1ULL if number is wider than unsigned long;
//promotion of 1UL << n doesn't happen until after evaluating 1UL << n where
//it's undefined behaviour to shift by more than the width of a long. T
//he same applies to all the rest of the examples.


/*
binary2int(unsigned char highlev, unsigned char lowlev){
  //copied code MUST MODIFY
  //https://stackoverflow.com/questions/37487528/how-to-get-the-value-of-every-bit-of-an-unsigned-char
//extracts bits from unsigned char and puts in an int array called bits
int lowbits[8];
for (int i = 0 ; i != 8 ; i++) {
    bits[i] = (lowlev & (1 << i)) != 0;
}

int highbits[8];
for (int i = 0 ; i != 8 ; i++) {
    highbits[i] = (highlev & (1 << i)) != 0;
}

*/
