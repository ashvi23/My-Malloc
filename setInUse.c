/*sets the in use bit , takes in an integer (functioning as a boolean), to tell it whether to assign the val to be either 1 or 0*/
void setInUse(int inUse, unsigned char* hiMeta){
    unsigned int mask=1<<7;
    unsigned int currBit=0;
  if(inUse==0){
    *hiMeta=(*hiMeta & ~mask) | ((currBit) & mask);
  } else if(inUse==1){
        currBit=1<<7;
	printf("currBit: ");
	printBinInt(currBit);
	printf("mask: ");
	printBinInt(mask);
	printf("*hiMeta: ");
	printSingleBin(*hiMeta);
	unsigned int combo=(*hiMeta & ~mask);
	printf("*hiMeta & ~mask: ");
	printBinInt(combo);
        *hiMeta=(*hiMeta & ~mask) | ((currBit) & mask);
  }
    return;
}
