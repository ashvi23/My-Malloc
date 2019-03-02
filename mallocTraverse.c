unsigned char* mallocTraverse(unsigned char* curr, int dataSize){
    *curr=myMem[2];
    while(curr>=lowerBound && curr<=upperbound){//lowerBound & upperBound will be global vars
      int currMeta=bin2int(*curr, *(curr+1));//converting chars to an int to send to getbit
      int inUse=getbit(currMeta, 1);//getting the in use bit
      char hiBits=getsizeBits(*curr);//blocking out in use bit to get size of block
      int currBlockSize=bin2int(hiBits, *(curr+1));//getting block size of current block
      if(inUse==0 && currBlockSize>=dataSize){//if there's enough space to return to the user
          curr=splitBlock(curr, currBlockSize, dataSize);//prepare it to return
          return curr+2;//return pointer to actual data block, not trying to overwrite metadata
      } else{
          curr=(curr+currBlockSize);
      }
    }
    /* got to end of array without finding an empty block */
    printf("Memory request exceeds size of working memory in file %d at line %d\n", __FILE__, __LINE__);
    return NULL;
}
