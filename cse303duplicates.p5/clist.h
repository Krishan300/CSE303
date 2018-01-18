#pragma once

#include <mutex>


//std::mutex g_num_mutex;
//std::lock_guard<std:mutex>lock(g_num_mutex);
/// TODO: complete this implementation of a thread-safe (concurrent) sorted
/// linked list of integers
class clist
{
	/// a Node consists of a value and a pointer to another node
  /*	struct Node
		{
		int value;
		Node* next;
	  Node(): value(0), next(NULL) {
	  }
	  };*/

	/// The head of the list is referenced by this pointer
  //  Node* head=new Node();
private:
  mutable std::mutex g_num_mutex;
  //  Node* head;

  struct Node{
    int value;
    Node* next;
  };
  
  Node* head;
public:
  //mutable std::mutex g_num_mutex;
   
  //Node* head;
        clist()
	: head(NULL)
        {}  
	  
	clist(int)
	: head(NULL)
	{}

      clist(const clist &other){

      }
  
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
	 
	   g_num_mutex.lock();
	   //printf("value we are inserting %d\n", key);
	   Node *a=create_Node(key);
	 
	 
	   if(head){
	   
	     if(key<head->value){
	   
	   
	       //  printf("value of head is %d\n", head->value);
	      a->next=head;
	      head=a;
	      //printList();
	      g_num_mutex.unlock();
	      return true;
	      
	     }
	    Node* start=head;
	   
	  
	    while(start->next){
	      //  printf("value of start %d\n", start->value);
	       if(start->value==key){
		 //printList();
		 g_num_mutex.unlock();
		
		 return false;
	       }
	       else if(start->next->value>key){
		 // printf("value of start is %d\n", start->value);
		 //printf("value of start's next is %d\n", start->next->value);
		a->next=start->next;
	        start->next=a;
		//printList();
		g_num_mutex.unlock();
		return true;
	      }
	       //  printf("value of start %d\n", start->value);
	      start=start->next;
	   
	    }
	   	   
	    //printf("value of start at end of list is %d\n",start->value);
	     if(start->value==key){
	       //printList();
	       g_num_mutex.unlock();
	       return false;
	     }
	     start->next=a;
	     //printList();
	     g_num_mutex.unlock();
	     return true;
	   

	   }
	   else{

	    
	      
	      
	     //printf("Beggining new list %d\n", a->value); 


	    head=a;
	    //printList();
	    g_num_mutex.unlock();
	    return true;
	 
	   
	   }
	}
	
	/// remove *key* from the list if it was present; return true if the key
	/// was removed successfully.
	bool remove(int key)
	{
	  
	  g_num_mutex.lock();
	  // printf("value we are removing %d\n", key);
	  if(!head){
	    
	    g_num_mutex.unlock();
	    return false;
	  }
	  Node *currentNode=head;

	  if(currentNode->value == key){
	    // printf("Removing head \n");
	    if(head->next){
	       head=currentNode->next;
	       // printf("New value of head is %d\n", head->value);
	    }
	    else{
	      head=NULL;
	    }
	    // printList();
	    g_num_mutex.unlock();
	    return true;
	  }
	  
		 
	   
	    
	  while(currentNode->next){
	        
	       
		if(currentNode->value>key){
		  // printf("value %d is greater than key\n",
		  // currentNode->value);
		  //printList();
		  g_num_mutex.unlock();
		  return false;
		}

		if(currentNode->next->value==key){
		    Node* RemovedNode=currentNode->next;
		    // printf("Removing value %d\n", currentNode->next->value);
		    if(RemovedNode->next){
		      currentNode->next=RemovedNode->next;
		      //printf("New value of currentNode->next is %d\n",currentNode->next->value);
		    }
		    else{
		      currentNode->next=NULL;
		    }

		    //printList();
		    g_num_mutex.unlock();
		    
		    return true;
		}
		
		     
		//printf("value of currentNode is %d\n", currentNode->value);
		     currentNode=currentNode->next;
		     

	  }

	  //printf("reached end of list. value of currentnode is
	  //%d\n", currentNode->value);
	  //printList();
		  g_num_mutex.unlock();
		  return false;
	}
	       
	 
		 
		

	   
	       
	


  
	/// return true if *key* is present in the list, false otherwise
	bool lookup(int key) const
	{
	       
	       g_num_mutex.lock();
	       //printf("we are looking up %d\n", key);
	        if(!head){
		 g_num_mutex.unlock();
		 return false;
		 }
	       
	     
	       Node *n=head;
	       while(n->next)
		 {
		  
		   
		   if(n->value == key)
		     {
		       //  printf("value of n is key %d\n", n->value);
		       g_num_mutex.unlock();
		       return true;
		     }
		   else if(n->value > key){
		     // printf("value of n is more than key key %d\n",n->value);
		     g_num_mutex.unlock();
		     return false;
		   }
		   //printf("value of n is %d\n", n->value);
		   n = n->next;
		 }
	       // printf("value of n at end of list is %d\n", n->value);
	       if(n->value == key){
		 g_num_mutex.unlock();
		 return true;
		 }
	       g_num_mutex.unlock();
	       return false;
	}
	     
	       /*   if(head->value==key){
	       g_num_mutex.unlock();
	       return true;
	     }
	     
		     
	       Node* start=head;
	       while(start->next){
		
		 if(start->value==key){
		
		   g_num_mutex.unlock();
		 
		   return true;
		 }
		 if(start->value>key){
		   g_num_mutex.unlock();
		 
		   return false;
		 }
		
		 start=start->next;
	       

	       }

	       if(start->value==key){
		 g_num_mutex.unlock();
		 return true;
	       }
	       g_num_mutex.unlock();
	       return false;*/
	       
	     
	   
	  
	
	
	
	  
	   
	     
	
	


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
	  /*if(index>getSize()){
	    printf("The index provided is greater than the size of the list");
	    return -1;
	    }*/
	  Node *start=head;
	  int j=0;
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


	//These functions just need to exist, they do not need to do anything
	size_t getBucketSize(size_t bucket) const
	{
		return 0;
	}
	int getElement(size_t bucket, size_t idx) const
	{
		return 0;
	}

  void printList(){
    Node *x=head;
    printf("This is list\n");
    while(x){
      printf("%d ", x->value);
      x=x->next;
    }

  }

};
