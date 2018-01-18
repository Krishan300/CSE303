#include "clist.h"
//#include "snode.h"
#pragma once
#include <mutex>
//#include "Snode.h"
#include <vector>
/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.  In
///       this implementation, each list should have a "sentinel" node that
///       contains the lock, so we can't just reuse the clist
///       implementation

class shash
{
private:
  struct Node{
    int value;
    Node* next;
  };

  
   struct Snode{
    Node* head;
    std::mutex snodelock;
   };
  /*    struct Node{
      int value;
      Node* next;
      };*/

   
    int num=0;
    std::vector<Snode*> bucketlist;
public:
  //std::vector<Snode*> bucketlist;
  Node* create_Node(int insert){
    Node *a=new Node();
    a->value=insert;
    a->next=NULL;
    return a;
  }

  shash(unsigned _buckets): num(_buckets)
  	{
	  int newsize=_buckets+((_buckets-1)*4);
	  bucketlist.resize(newsize);
	  for(int i=0; i<newsize; i++){
	    bucketlist[i]=new Snode;
	    bucketlist[i]->head=NULL;
	    
	  }
         	 
	  /* for(int i=0; i<_buckets; i++){
          
	   bucketlist[i].setlistptr(&buckets[i]);
	   }*/
	  
	}

       

  /* shash(unsigned _buckets){
  }*/

   
          
        /// insert *key* into the appropriate linked list if it doesn't already
	/// exist; return true if the key was added successfully.
	bool insert(int key)
	{

	  int b = (key % num)*5;
	  //printf("%d\n", b);
	  bucketlist[b]->snodelock.lock();
	  //printf("value we are inserting %d\n", key);
	  Node *a=create_Node(key);
	  
	  if(bucketlist[b]->head){
	    
	    Node* start=bucketlist[b]->head;
	    if(key<start->value){
	      a->next=start;
	      bucketlist[b]->head=a;
	      //printList(bucketlist[b]->head);
	      bucketlist[b]->snodelock.unlock();
	     
	      return true;
	    }
	    while(start->next){
	      if(start->value==key){
		//printf("valud of start %d\n", start->value);
		//printList(bucketlist[b]->head);
		bucketlist[b]->snodelock.unlock();
		return false;
	      }
	      if(start->next->value>key){
		//printf("valud of start %d\n", start->value);
		//printf("value we are replacing %d\n", start->next->value);
		a->next=start->next;
		//printf("new value %d\n", start->next->value);
		start->next=a;
		//printf("new value %d\n", start->next->value);
		//printList(bucketlist[b]->head);
		bucketlist[b]->snodelock.unlock();
		return true;
	      }
	      //printf("value of start is %d\n", start->value);
	      start=start->next; 
	    }
	    //printf("we have reached end of list with %d\n", start->value);
	    if(start->value==key){
	      // printList(bucketlist[b]->head);
	      bucketlist[b]->snodelock.unlock();
	      //printList(bucketlist[b]->head);
	      return false;
	    }
	    start->next=a;
	    //printList(bucketlist[b]->head);
	    bucketlist[b]->snodelock.unlock();
	    return true;
	  }
	  
	  else{
	    bucketlist[b]->head=a;
	    //printList(bucketlist[b]->head);
	    //printf("no head");
	    //printf("new value of head is %d\n", bucketlist[b]->head->value);
	    bucketlist[b]->snodelock.unlock(); 
	    return true;
	  }
	   
	 		
	}
	/// remove *key* from the appropriate list if it was present; return true
	/// if the key was removed successfully.
	bool remove(int key)
	{
	  int b = (key % num)*5;
	 
	  bucketlist[b]->snodelock.lock();
	  //printf("value we are removing is %d\n", key);
	  if(bucketlist[b]->head){
	    Node* currNode=bucketlist[b]->head;
	    if(currNode->value==key){
	      if(currNode->next){
		bucketlist[b]->head=currNode->next;
	      
	      }
	      else{
		bucketlist[b]->head=NULL;
	      }
	      //printlist(bucketlist[b]->head);
	      bucketlist[b]->snodelock.unlock();
	     
	      return true;
	    }
	    while(currNode->next){
	      if(currNode->value>key){
		//	printlist(bucketlist[b]->head);
		bucketlist[b]->snodelock.unlock();
		return false;
	      }
	      else if(currNode->next->value==key){
		Node* RemoveNode=currNode->next;
		if(RemoveNode->next){
		  currNode->next=RemoveNode->next;
		}
		else{
		  currNode->next=NULL;
		}
		//printlist(bucketlist[b]->head);
		bucketlist[b]->snodelock.unlock();
		
		return true;
	      }
	      // printf("value of currNode is %d\n", currNode->value);
	      currNode=currNode->next;
	    }

	    if(currNode->value==key){
	      currNode=NULL;
	      //printlist(bucketlist[b]->head);
	      bucketlist[b]->snodelock.unlock();
	      return true;
	    }
	    //printlist(bucketlist[b]->head);
	    bucketlist[b]->snodelock.unlock();
	    return false;
	  }

	  else{
	   
	    bucketlist[b]->snodelock.unlock();
	    return false;
	  }
        

	}
	  
	 
	  //      int b = key % num;
	       
	  //   return bucketlist[b].remove(key);
		
			  /*bucketlist[b].g_num_mutex.lock();
		remove=(bucketlist[b].listptr)->remove(key);
		bucketlist[b].g_num_mutex.unlock();*/
	        
		
	/// return true if *key* is present in the appropriate list, false
	/// otherwise
	bool lookup(int key) 
	{

	  // printf("value we are looking up is %d\n", key);
	  //bool lookup=true;
	  int b = (key % num)*5;
	  bucketlist[b]->snodelock.lock();
	  Node* curr=bucketlist[b]->head;
	  while(curr){
	    /*    if(curr->value>key){
	      bucketlist[b]->snodelock.unlock();
	      return false;
	      }*/
	       if(curr->value==key){
	      //printf("true\n");
	      // printList(bucketlist[b]->head);
	      bucketlist[b]->snodelock.unlock();
	      //    printList();
	      /// printf("%s\n", true);
	      return true;
	    }
	    curr=curr->next;
	  }
	  //printList(bucketlist[b]->head);
	  //printf("false\n");
	  bucketlist[b]->snodelock.unlock();
	  return false;
	  
	  //return bucketlist[b].lookup(key);
	  
	  
	}

	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.

	//This refers to the number of buckets not the total number of
	//elements.
  
	size_t getSize() const
	{
	  return (num+((num-1)*4));
	}


        size_t snodesize()
        {
	  
	  return (sizeof(Snode*));
	}

	//This refers to the number of elements in a bucket, not the sentinel node.
	size_t getBucketSize(size_t bucket) const
	{
	  int bucketpos=static_cast<int>(bucket);
	  if(bucketpos>num-1){
	    return -1;
	  }
	  int elementnumber=0;
	  Node *start=bucketlist[(bucketpos)*5]->head;
	  while(start){
	    elementnumber+=1;
	    start=start->next;

	  }
	  return elementnumber;
	}
  

       int getElement(size_t bucket, size_t idx) const
	{
	  int bucketpos=static_cast<int>(bucket);
	  if(bucketpos>num-1){
	    return -1;
	  }
	  Node *start=bucketlist[(bucketpos)*5]->head;
	  int j=0;
	  while(start){
	    if(j==idx){
	      return start->value;
	    }
	    j=j+1;
	    start=start->next;
	  }
	  return -1;
	}


	//These functions just need to exist, they do not need to do anything
	int getElement(size_t idx) const
	{
		return 0;
	}
        static void printList(Node* head){
	  while(head){
            printf("%d\n", head->value);
	    head=head->next;
	  }
        }
};
