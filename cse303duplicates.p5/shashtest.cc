//#pragma once
#include <mutex>
#include <thread>
//#include "Snode.h"
#include <vector>
#include "shash.h"

int main(){

  shash* a=new shash(12);
  bool results[3];
  int insertvals[]={1,17,9};
  int num=3;

  for(int i=0; i<100;i++){
    a->insert(i);
  }

  /*  for(int i=0; i<50;i++){
    a->remove(i);
    }*/
  printf("size of bucket one is %d\n", a->getBucketSize(0));
  a->remove(0);
  printf("size of bucket one is %d\n", a->getBucketSize(0));
  printf("size of bucket fifteen is %d\n", a->getBucketSize(15));
  a->remove(63);
  printf("size of bucket fifteen is %d\n", a->getBucketSize(15));
  printf("size of bucket sixteen is %d\n", a->getBucketSize(16));
  a->insert(122);
  a->insert(111);
  printf("size of bucket fifteen is %d\n", a->getBucketSize(15));
  
  //  a->remove(36);
  a->remove(4);
  // a->remove(25);
  a->remove(96);
  printf("insserting one ninety\n");
  a->insert(190);
  printf("%d\n", a->getBucketSize(12));
  //a->remove(99);
  //  a->remove(0);

  for(int i=0; i<16; i++){
    printf("\n");
    for(int j=0; j<16; j++){
      printf("%d ",a->getElement(i,j));
    }
  }

  
  //  a->insert(insertvals, results, 3);

 
 
 
  /*for(int i=0; i<16; i++){

    a->printList(a->bucketlist[i]->head);
    }*/
  
  printf("%d\n", a->snodesize());
}
