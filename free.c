myfree(){

}
combinemetadata(char* curr, char* prev){
  /*
  - prev = inuse curr next = inuse
  - prev = !inuse curr next = inuse
  - prev = !inuse curr next = !inuse
  - prev = inuse curr next = !inuse

  check left
  if prev = free
  extract 16-1 rightmost bits (the size bits) on curr
  bin2int size bits on curr
  extract size bits from prev
  bin2int size bits on prev
  bitadd prevsize curr size
  int2bin sum
  change prev ptr size to sum bits
  set char ptr curr in use bit to 0

  check right
  if prev! freeblocks
  check if curr + metadata at(currsize + sizeof(metadata)) is free
  extract 16-1 rightmost bits (the size bits) on curr
  bin2int size bits on curr
  extract size bits from prev
  bin2int size bits on prev
  bitadd prevsize curr size
  int2bin sum
  change prev ptr size to sum bits
  set char ptr curr in use bit to 0

  if left in use and right in Use
    do nothing. there is nothing to combine.

  */
}
travmeta(){

}
checkptr(){
/*
checks if the pointer given to free is a valid ptr pointing at the start of block
while()
*/
}


int main (int argc, char**argv){

}
