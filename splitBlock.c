unsigned char* splitBlock(unsigned char* curr, int blockSize, int dataSize){
     unsigned char* hi=curr;
     unsigned char* lo=curr+1;
     setBlock(1, *hi);  t
      if((blockSize-3)>dataSize){//if block can fit at least two bytes of free space, including metadata, make free space
          //set in use bit to in use

          //subtract number of bits of free space (+ metadata space) from size of currBit
          splitBin(dataSize, hi, lo);
          hi=curr+dataSize+2;;//iterate our new pointers along
          lo=hi+1;
          blockSize=blockSize-dataSize-2;
          *hi=0;
          *lo=0;
          splitBin(dataSize, hi, lo);//set metadata for new metadata block
          setBlock(1, *hi);
          //zero out what was there, set in use bit to 0, size bit to above size
          //set curr equal to dataSize blocks behind
          //return curr
      }
      return curr;
}
