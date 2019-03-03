int main (int argc, char**argv){
int *ptrarr[150];


// case a
for(int i =0 ; i< 150; i++){
  char* ptr = (char*) malloc(1 * sizeof(char));
  free(ptr);
}


//case b

int malcounter=0;
int *ptr;
for(int i =0; i< 150; i++){
  ptrarr[i] = (int*) malloc(1);
}
for (int j =0; j<150;j++ ){
  free(ptrarr[i]);
}

// case c
malcounter = 0;
int freedptr = 0;
int ptr2free =malcounter - freedptr;
int freeindex =0;
int* pointers[50];
int mallocindex =0;

  int random = rand()%2;
  while(malcounter <=50){
    if(random == 0){ //malloc if 0
      pointers[mallocindex] = (int*)malloc(1);
      malcounter++;
      i++
    }
    else if (rand == 1){ // free if 1
      if (ptr2free != 0){
        free(pointers[freeindex]);
        pointers[freeindex] = NULL;
        freeindex++;
        freedptr++;
        ptr2free =malcounter - freedptr;
      }

    }
    if(malcounter== 50){
      break;
    }
    random = rand()%2;
    }
    if (malcounter == 50){
      while(ptr2free!= 0){
        free(pointers[freeindex]);
        pointers[freeindex] = NULL;
        freedptr++;
        freeindex++;
        ptr2free= malcounter-freedptr
      }
    }

  //case d
  int memleft=4092;
  int memalloc =0;
  int* pointers2[50];
  freedptr=0;
  freeindex=0;
  malcounter=0;
  ptr2free =0;
  mallocindex=0;
  int memarr[50];
//  int random = rand()
while(malcounter<=50){
  if (memleft >0){
    random = rand()%2;
    if(random ==0){
      random = rand();
      while(random < 1 || random > 64){
        random = rand();
        if (random <=64 && random >= 1){
          break;
        }
      }
      if(memleft >=random){
        pointers2[mallocindex]= (int*)malloc(random);
        memarr[mallocindex] = random;
        memalloc +=random;
        mallocindex++;
        malcounter++;
        memleft-=random;
      }

    }
    else if (random ==1){
      if(ptr2free!=0){
        free(pointers2[freeindex]);
        freeindex++;
        freedptr++;
        ptr2free = malcounter-freedptr;
        memleft =

      }
    }
  }
  if (malcounter ==50){
    break;
  }
}
if(malcounter ==50){
  while(ptr2free>0){
    free(pointers2[freeindex]);
    freeindex++;
    freedptr++;
    ptr2free = malcounter-freedptr;

    if(ptr2free == 0){
      break;
    }
  }

}


  while(memoryleft!=0){
    random = rand()%2;
    if(random == 0){
      random = rand();
      while(random < 1 || random > 64){
        random = rand();
        if (random <=64 && random >= 1){
          break;
        }
      }
      //actually malloc stuff here
      if(memleft >=random && malcounter<50){
        pointers2[mallocindex]= (int*)malloc(random);
        memarr[mallocindex] = random;
        memalloc +=random;
        mallocindex++;
        malcounter++;
        memleft-=random;
      }
    }
    else {
      if(ptr2free!=0){
        free(pointers2[freeindex]);
        freeindex++;
        freedptr++;
        ptr2free = malcounter-freedptr;
        memleft =

      }
    }

  }


return 0;
}
