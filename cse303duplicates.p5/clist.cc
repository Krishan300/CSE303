#include "clist.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
using namespace std;
//Node* head;
//head->value=False;
//head->next=NULL;

class clist(){
public:
  Node* head=new Node;
  head->value=NULL;
  head->next=NULL;

 

  bool insert(int insertvalue){
   
    Node* start=head;
    printf("%d\n", insertvalue);
    Node *a;//=create_Node(insertvalue); 
    while(head->next){
      start=head->next;
      if(start->next->value>insertvalue){
        a=create_Node(insertvalue);
	a->next=start->next;
	start->next=a;
	return true;
      }
      
    }
     a=create_Node(insertvalue);
    start->next=a;
    return true; 


  }

  Node *create_Node(int nodeval){
    Node *a=new Node*;
    Node->value=nodeval;

  }





}
