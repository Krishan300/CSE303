#include "chash.h"

int main(){
  chash *a=new chash(12);
  for(int i=0; i<101; i++){
    a->insert(i);
  }
  a->remove(0);
  a->remove(96);
  a->remove(100);
  a->remove(11);
  for(int i=0; i<12; i++){
    printf("\n");
    for(int j=0; j<9; j++){
      printf("%d ",a->getElement(i,j));
    }
  }
  
  printf("Size of bucket 5 is %d\n", a->getBucketSize(5));
  printf("Size of bucket 1 is %d\n", a->getBucketSize(0));
  a->remove(12);
  printf("Size of bucket 1 is %d\n", a->getBucketSize(0));
}
