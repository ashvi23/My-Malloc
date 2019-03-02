unsigned char* mallocTraverse(unsigned char* curr, int dataSize){
    *curr=myMem[2];
    while(curr>=lowerBound && curr<=upperbound){//lowerBound & upperBound will be global vars
      int currMeta=bin2int(*curr, *(curr+1));
      int inUse=getbit(currMeta, 15);//hopefully this works
      char hiBits=getsizeBits(*curr);//blocking out in use bit
      int currBlockSize=(hiBits, *(curr+1));//getting block size of current block
      if(inUse==0 && currBlockSize>=dataSize){
          curr=splitBlock(curr, currBlockSize, dataSize);

      } else{
          curr=(curr+currBlockSize);
      }
      return curr;
    }
    printf("Memory full\n");
    return NULL;
}
