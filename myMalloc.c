//main: if first (2? 4?) bytes arent set to key, set key, and set the first piece of metadata.

/*split method: see how much data user is requesting (takes pointer to metadata block, amount of space user requested)
at first instance of a space big enough

                      error checking: did user ask for too much?
                      -->if space is bigger than requested
                      --> reduce
                          -->if too small for metadata+2 bytes, return the whole thing to user as is
                          else: --> make new metadata, set size to the value originally stored for size of currblock MINUS size of space being allocated MINUS
                          size of metadata
                          else if space==size:
                          continue
                          else if no eligible space: print error message
                        traverse array method(returns pointer):
                        while index!=4095
                        if in use bit==flipped
                        bintoInt-> traverse that many spaces onward
                        move to next
                        else    bin2Int ->compare to amount of space user asks for, if too small move on
                        else return pointer to space */
//  make global vars with the address range of the array, size of metadata, key
void* myMalloc(int size, __FILE__, __LINE__){
  unsigned char* first=myMem[0];
  unsigned char* second=myMem[1];
  unsigned char* ptr= myMem[0];
  int firstBytes=bit2int(*first, *second);
  if(firstBytes!=key){//set key to initialize method
    int usrBlock=4092;//size of arr-metadata bits- size of key
    *ptr=key;
    ptr=ptr+2;
    first=ptr;//initialize metadata after key
    second=ptr+1;
    *first=0;
    *second=0;
    splitBin(usrBlock, first, second);//set metadata for new metadata block
    setBlock(0, *hi);
  }
  if(size>usrBlock || size<0){//if user tries to allocate more memory than size of array/metadata/key allows for, or a negative value
      if(size>usrBlock){
      printf("Memory request exceeds size of working memory in file %d at line %d\n", __FILE__, __LINE__);
      return NULL;
    } else{
      printf("Invalid memory request in file %d at line %d\n", __FILE__, __LINE__);
    }
  }else{
    ptr=mallocTraverse(ptr, size);//calling the meat of the program, returns either a pointer to usable memory or a null pointer
  }
  return (void*)ptr;
}
