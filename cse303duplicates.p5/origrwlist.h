#pragma once
#include <pthread.h>
/// TODO: complete this implementation of a thread-safe (concurrent) sorted
/// linked list of integers, which should use readers/writer locking.
class rwlist
{
        mutable pthread_rwlock_t lock_rw = PTHREAD_RWLOCK_INITIALIZER;
	/// a node consists of a value and a pointer to another node
	struct Node
	{
		int value;
		Node* next;
	};

	/// The head of the list is referenced by this pointer
	Node* head;

     

  //private:
  //mutable pthread_rwlock_t lock_rw = PTHREAD_RWLOCK_INITIALIZER;


public:
  // mutable pthread_rwlock_t lock_rw = PTHREAD_RWLOCK_INITIALIZER;
       rwlist()
       : head(NULL)
       {}
	rwlist(int)
	: head(NULL)
	{}


     Node* create_Node(int insert){
	  Node *a=new Node();
	  a->value=insert;
	  a->next=NULL;
	  return a;
	    
	}   
	  
	/// insert *key* into the linked list if it doesn't already exist; return
	/// true if the key was added successfully.
	bool insert(int key)
	{
	  
	       pthread_rwlock_wrlock(&lock_rw);
	       // printf("we are inserting %d\n", key);
	       Node *a=create_Node(key);
	       if(head){
	
		 
		 
		 
		 if(key<head->value){
		   // printf("value of head is %d\n", head->value);
		   a->next=head;
		   head=a;
		   //printf("new value of head is %d\n", head->value);
		   pthread_rwlock_unlock(&lock_rw);
		   return true;
		 }
	       
		 Node* start=head;
		 while(start->next){
		   if(start->value==key){
		     pthread_rwlock_unlock(&lock_rw);
		     return false;
		   }
		   //printf("value of start is %d\n", start->value);
		    else if(start->next->value>key){
		      //  printf("value of start is %d\n", start->value);
		     
		      a->next=start->next;
		      start->next=a;
		      pthread_rwlock_unlock(&lock_rw);
		      return true;
		   }
		   // printf("value of start is %d\n", start->value); 
		   start=start->next;
		 }
		 //printf("End of list: value of start is %d\n", start->value);
		 if(start->value==key){
		   pthread_rwlock_unlock(&lock_rw);
		   return false;
		 }
		 start->next=a;
		 pthread_rwlock_unlock(&lock_rw);
		 return true;
	       }
	       else{
		 head=a;
		 pthread_rwlock_unlock(&lock_rw);
		 return true;
	       }
	}
	/// remove *key* from the list if it was present; return true if the key
	/// was removed successfully.
	bool remove(int key)
	{
	        pthread_rwlock_wrlock(&lock_rw);
		//printf("value to remove is %d\n", key);
		Node* a;
		Node* RemovedNode;
		if(head){
		  //printf("value of head is %d\n", head->value);
		  if(head->value==key){
		    if(head->next){
		      head=head->next;
		      //  printf("new value of head is %d\n", head->value);
		    }
		    else{
		      head=NULL;
		    }
		 
		     pthread_rwlock_unlock(&lock_rw);
		     return true;
		 }
		 a=head;
		while(a->next){
		  
		  if(a->value>key){
		    pthread_rwlock_unlock(&lock_rw);
		    //printf("value of a is %d\n", a->value);
		    return false;
		  }
		  
		  if(a->next->value==key){
		    //printf("Removing  %d\n", a->next->value);
		     Node* RemovedNode=a->next;
		     if(RemovedNode->next){
		       a->next=RemovedNode->next;
		       // printf("New value of a->next is %d\n", a->next->value);
		     }
		     else{
		       a->next=NULL;
		     }
		     pthread_rwlock_unlock(&lock_rw);
		     return true;
		  }
		  //printf("Value of a is %d\n", a->value);
		  a=a->next;
		}

		//	printf("End of list, value of a is %d\n", a->value);
		
		pthread_rwlock_unlock(&lock_rw);
		return false;
		}
		else{
		  pthread_rwlock_wrlock(&lock_rw);
		  return false;
		}
	}
	/// return true if *key* is present in the list, false otherwise
	bool lookup(int key) const
	{
	        pthread_rwlock_rdlock(&lock_rw);
		//printf("we are looking up %d\n", key);
		//bool lookup=false;
		/*	if(head->value==key){
		  printf("true\n");
		  pthread_rwlock_unlock(&lock_rw);
		  return true;
		  }*/
	
	
		Node* start=head;
		
		while(start){
		  // printf("%d\n",start->value);
		  if(start->value==key){
		    
		    // printf("true\n");
		    pthread_rwlock_unlock(&lock_rw);
		    return true;
		  }
		  if(start->value>key){
		    //printf("false\n");
		    pthread_rwlock_unlock(&lock_rw);
		    // printf("false\n");
		    return false;
		  }
		  start=start->next;
		  //printf("value we see while looking up %d\n", start->value);
		}

		/*	if(start->value==key){
		  pthread_rwlock_unlock(&lock_rw);                         
		    return true;
		  
		    }*/
		pthread_rwlock_unlock(&lock_rw);
	
		return false;
	}

	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.
	size_t getSize() const
	{
	  size_t listsize=0;
	  Node *start=head;
	  while(start){
	    listsize+=1;
	    start=start->next;

	  }
	  return listsize;
	}

       int getElement(size_t idx) const
	{
	  int index=static_cast<int>(idx);
	 
	  int j=0;
	  Node *start=head;
	  int elementdata=0;
	  while(start){
	    if(j==index){
	      elementdata=start->value;
	      return elementdata;
	    }
	    j=j+1;
	    start=start->next;
	  }
	  return -1;
								
	}

  void printList(){
    Node *x=head;
    printf("This is list\n");
    while(x){
      printf("%d ", x->value);
      x=x->next;
    }

  }

	//These functions just need to exist, they do not need to do anything
	size_t getBucketSize(size_t bucket) const
	{
		return 0;
	}
	int getElement(size_t bucket, size_t idx) const
	{
		return 0;
	}
};
