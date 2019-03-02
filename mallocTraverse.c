unsigned char* mallocTraverse(unsigned char* curr, int dataSize){
    *curr=myMem[2];
    while(curr>=lowerBound && curr<=upperbound){//lowerBound & upperBound will be global vars
      int currMeta=bin2int(*curr, *(curr+1));
      int inUse=getbit(currMeta, 1);//hopefully this works
      char hiBits=getsizeBits(*curr);//blocking out in use bit
      int currBlockSize=bin2int(hiBits, *(curr+1));//getting block size of current block
      if(inUse==0 && currBlockSize>=dataSize){
          curr=splitBlock(curr, currBlockSize, dataSize);
          return curr+2;
      } else{
          curr=(curr+currBlockSize);
      }
    }
    /* got to end of array without finding an empty block */
    printf("Memory request exceeds size of working memory in file %d at line %d\n", __FILE__, __LINE__);
    return NULL;
}
