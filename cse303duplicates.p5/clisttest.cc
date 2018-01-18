#include <stdio.h>
#include "clist.h"
#include "rwlist.h"
#include <pthread.h>
#include <mutex>

int main(){
  clist* a=new clist();
  a->insert(3);
  a->insert(5);
  a->insert(3);
  a->remove(5);
  a->insert(500);
  a->insert(500);
  a->insert(2);
  a->printList();
  printf("%zu\n",a->getSize());
  size_t y=5;
  printf("%d\n", a->getElement(2));
  printf("%d\n", a->getElement(4));
  rwlist* b=new rwlist();
  for(int i=0; i<100; i++){
    b->insert(i);
  }
  for(int j=59; j<200; j++){
    b->remove(j);
  }
  b->printList();
  //printf("%d\n", a->getElement(0));

}
