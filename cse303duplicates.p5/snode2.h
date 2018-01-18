#pragma once
#include <vector>
#include "clist.h"

#include "Node.h"


class snode2{
  // std::mutex newmutex;
  // std::unique_ptr<std::mutex> newmutex =
  // std::make_unique<std::mutex>();
  // private:
  //mutable std::mutex oldmutex;

  public:
  // using Lock = std::unique_lock<std::mutex>;
   mutable std::mutex newmutex;
   Node *listptr;

  Node* create_Node(int insert){
    Node *a=new Node();
    a->value=insert;
    a->next=NULL;
    return a;
  }
  
  snode2(): listptr(NULL) {
    // printf("called here \n");
    std::lock_guard<std::mutex> (this->newmutex);
    
    //std::unique_lock<std::mutex> newmutex = std::unique_lock<std::mutex> (oldmutex);
  }

  //snode2(const snode2& a){
    
  // }
  snode2(const snode2& a){
   
    // std::lock_guard<std::mutex> (a.newmutex);
    //printf("called here \n");
     listptr=a.listptr;
  }

  /*  snode(snode &&other){
    std::lock_guard<std::mutex> lock(other.mtx);
    listptr=std::move(other.listptr);

    }*/


  void setlistptr(clist *a){
   
    this->listptr=a->head;
  }

  bool insert(int key){
    newmutex.lock();
    //printf("locked aquired\n");
    // boost::mutex::scoped_lock newmutex(oldmutex);
    // std::unique_lock<std::mutex> newmutex(oldmutex);
    //printf("value we are inserting is %d\n", key);
    Node *a=create_Node(key);
    //  Node *start=listptr;
    if(listptr){
	                                         
       if(key<listptr->value){
	      a->next=listptr;
	      listptr=a;
              newmutex.unlock();
	      return true;
         }
      Node *start=listptr; 
      while(start->next){
	 if(start->value==key){
	   //   printf("value of start is key %d\n", start->value);
	   newmutex.unlock();
	  
	   return false;
	 }
	 else if (start->next->value>key){
	 
	   //printf("value of start is %d\n", start->value);
	   //printf("value of start->next is %d\n", start->next->value);
	   a->next=start->next;
	   start->next=a;
	   // printf("new value of start->next is %d\n", start->next->value);
	   newmutex.unlock();
	   return true;
	 }
	 // printf("value of start is %d\n", start->value);
	 start=start->next;
       }
      // printf("value of start at end of list is %d\n", start->value);
       if(start->value==key){
	
	 newmutex.unlock();
	 return false;
       }
       start->next=a;
       newmutex.unlock();
       return true;
    }
    else{
      listptr=a;
      newmutex.unlock();
      return true;
     }
  }
  bool remove(int key){
    newmutex.lock();
    //printf("lock aquired/n");
    //boost::mutex::scoped_lock newmutex(oldmutex);
    //  std::unique_lock<std::mutex> newmutex = std::unique_lock<std::mutex> (oldmutex);
    //printf("we are removing %d\n", key);
     //Node* start=listptr;
     if(listptr){
       if(listptr->value==key){
	 // printf("key is head %d\n", key);
	 if(listptr->next){ //set listptr to next if has a next
	   listptr=listptr->next;
	   // printf("new val of head is %d\n", listptr->value);
	 }
	 else{
	   listptr=NULL;
	 }
	 newmutex.unlock();
	 return true;
          }
       Node* start=listptr;
       while(start->next){
	 //printf("value of start is %d\n", start->value);
	 if(start->value>key){
	   // printf("value of start is greater then key %d\n", start->value);
	   newmutex.unlock();
	   return false;
	 }
	 else if(start->next->value==key){
	   // printf("value of start is %d\n", start->value);
	   //printf("value of start->next is key %d\n", start->next->value);
	   Node *RemovedNode=start->next;
	   if(RemovedNode->next){
	     start->next=RemovedNode->next;
	     //printf("new value of start->next %d\n", start->next->value);
	   }
	   else{
	     start->next=NULL;
	   }

	   newmutex.unlock();
	   return true;
	 }

	 //printf("value of start is %d\n", start->value);
	 start=start->next;

       }
       //printf("reached end of list. value of start is %d\n", start->value);
       /*      if(start->value==key){
	 start=NULL;
	 newmutex.unlock();
	 return true;
	 }*/
       newmutex.unlock();
       return false;
     }
       else{
	 newmutex.unlock();
	 return false;

       }
       /* bool remove=true;
    remove=(listptr->remove(key));
    newmutex.unlock();
    return remove;*/
     }
     

  bool lookup(int key) const{
    newmutex.lock();
    //boost::mutex::scoped_lock newmutex(oldmutex);
      //std::unique_lock<std::mutex> newmutex = std::unique_lock<std::mutex> (oldmutex);
    //printf("value we are looking for is %d\n", key);
    if(listptr){
      Node *start=listptr;
      while(start){
	//printf("value of start is %d\n", start->value);
	if(start->value==key){
	  //printf("key is %d\n", start->value);
	  newmutex.unlock();
	  return true;
	}
	else if(start->value>key){
	  // printf("leaving list at %d\n", start->value);
	  newmutex.unlock();
	  return false;
	}
	start=start->next;
      }
      /*     if(start->value==key){
	newmutex.unlock();
	return true;
	}*/
      newmutex.unlock();
      return false;

    }
    else{
      newmutex.unlock();
      return false;

    }
    /* newmutex.lock();
    bool lookup=true;
    lookup=(listptr->lookup(key));
    newmutex.unlock();
    return lookup;*/
    

  }


};
