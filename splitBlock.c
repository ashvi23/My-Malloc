unsigned char* splitBlock(unsigned char* curr, int blockSize, int dataSize){
     unsigned char* hi=curr;
     unsigned char* lo=curr+1;
     setBlock(1, *hi);
      if((blockSize-3)>dataSize){//if block can fit at least two bytes of free space, including metadata, make free space
          splitBin(dataSize, hi, lo);//set curr's size to the size of data requested (truncating it)
          hi=curr+dataSize+2;//iterate our new pointers along
          lo=hi+1;
          blockSize=blockSize-dataSize-2;//blocksize of free block created when you allocate less than space in curr block
          *hi=0;//zero out  garbage vals in these bytes
          *lo=0;
          splitBin(blockSize, hi, lo);//set metadata for new metadata block
          setBlock(0, *hi);
      }
      return curr;//curr was never iterated so we can return it as-is
}
