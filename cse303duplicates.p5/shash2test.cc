//#pragma once
#include <mutex>
#include <thread>
//#include "Snode.h"
#include <vector>
#include "shash2.h"

int main(){

  shash2* a=new shash2(16);
  bool results[100];
  
  //int
  //insertvals[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,14,15,16,19,20,12,21,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42};
  int insertvalues[100];
  for(int i=0; i<100;i++){
    insertvalues[i]=i;
  }
  int num=sizeof(insertvalues)/sizeof(int);

  
  a->insert(insertvalues,results,num);
 

  int removevalues[50];
  for(int i=0; i<50;i++){
    removevalues[i]=i;
  }
  bool newresults[50];
  
   a->remove(removevalues,newresults,50);

  a->newinsert(115);

  a->newremove(50);

  for(int i=0; i<16; i++){
    printf("\n");
    for(int j=0; j<16; j++){
      printf("%d ",a->getElement(i,j));
    }
  }
  //  a->newinsert(115);
  // a->newremove(50);
  /*  for(int i=0; i<50;i++){
    a->remove(i);
    }*/
  /*printf("size of bucket one is %d\n", a->getBucketSize(0));
  a->remove(0);
  printf("size of bucket one is %d\n", a->getBucketSize(0));
  printf("size of bucket fifteen is %d\n", a->getBucketSize(15));
  a->remove(63);
  printf("size of bucket fifteen is %d\n", a->getBucketSize(15));
  printf("size of bucket sixteen is %d\n", a->getBucketSize(16));
  a->insert(122);
  a->insert(111);
  printf("size of bucket fifteen is %d\n", a->getBucketSize(15));
  a->insert(0);
  //  a->remove(36);
  a->remove(4);
  a->remove(25);
  printf("insserting one ninety\n");
  a->insert(190);*/
  //a->remove(99);
  //  a->remove(0);

  //  int removevalues[50];
  for(int i=0; i<50;i++){
    removevalues[i]=i;
  }
  //bool newresults[50];
  //int newnum=50;
  printf("%d\n",a->getBucketSize(0));
  // a->remove(removevalues,newresults,newnum);
  // printf("%d\n",a->getBucketSize(0));
   printf("%d\n", a->getBucketSize(3));
  a->newinsert(115);
  printf("%d\n", a->getBucketSize(3));
  a->newremove(32);
  printf("size of 12 is %d\n", a->getBucketSize(12));
  
  a->newremove(12);
  printf("size of 12 is %d\n", a->getBucketSize(12));
  for(int i=0; i<16; i++){
    printf("\n");
    for(int j=0; j<16; j++){
      printf("%d ",a->getElement(i,j));
    }
  }
  
  a->newremove(15);

  int newinsert[80];
  for(int i=0; i<80;i++){
    newinsert[i]=112+(i*16);
  }

  bool newbool[80];

  int rnewnum=sizeof(newinsert)/sizeof(int);

  a->newremove(50);  
  a->insert(newinsert,newbool,rnewnum);
  printf("%d\n",a->getBucketSize(0));
  for(int i=0; i<16; i++){
    printf("\n");
    for(int j=0; j<16; j++){
      printf("%d ",a->getElement(i,j));
    }
  }
  a->remove(removevalues,newresults,50);                                 
  for(int i=0; i<16; i++){
    printf("\n");
    for(int j=0; j<16; j++){
      printf("%d ",a->getElement(i,j));
    }
  }
  //  a->insert(insertvals, results, 3);

   
  a->newinsert(111);
  printf("%d\n",a->getBucketSize(15));
 
  /*for(int i=0; i<16; i++){

    a->printList(a->bucketlist[i]->head);
    }*/
  
  //  printf("%d\n", a->snodesize());
}
