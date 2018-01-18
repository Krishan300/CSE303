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

class shash2
{
private:

   bool* islockacquired;
  mutable std::mutex ourmutex;
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

   
    int Bnum=0;
   std::vector<Snode*> bucketlist;
  //int **matrix;
     std::vector<std::vector<int>> matrix;
     
public:

  //  std::vector<Snode*> bucketlist; 
//mutable std::mutex ourmutex;
  // bool* islockacquired;
    Node* create_Node(int insert){
    
    Node *a=new Node();
    a->value=insert;
    a->next=NULL;
    return a;
  }


  // int **values=(int **)malloc(sizeof(int*)*16);
  shash2(unsigned _buckets): Bnum(_buckets)
  	{
	  int newsize=_buckets+((_buckets-1)*4);
	  bucketlist.resize(newsize);
	  for(int i=0; i<newsize; i++){
	    bucketlist[i]=new Snode;
	    bucketlist[i]->head=NULL;
	    
	  }
	  islockacquired=new bool[newsize];
	  for(int i=0; i<newsize; i++){
	    islockacquired[i]=false;
	  }


	  matrix.resize(_buckets);
	 
	  for (int i=0; i<_buckets; i++){
	    std::fill(matrix[i].begin(), matrix[i].end(), -1);
	  }
	  //int **values=(int **)malloc(sizeof(int*)*_buckets);
         	 
	  /* for(int i=0; i<_buckets; i++){
          
	   bucketlist[i].setlistptr(&buckets[i]);
	   }*/
	  
	}

 
  /*  std::vector<std::vector<int>> sorter(int *keys, std::vector<std::vector<int>> matrix, int num){
    //ourmutex.lock();
    for(int i=0; i<num; i++){
      int b=keys[i]%Bnum;
      //  printf("matrix we are inserting into is %d\n", b);
      printf("value of buckets is %d\n", Bnum);
      printf("value we are inserting %d\n", keys[i]);
      printf("matrix we are inserting into is %d\n", b);
      matrix[b].insert(keys[i]);
    }
    
    return matrix;

    }*/

  void insert(int *keys, bool* results, int num){

    //  ourmutex.lock();
    int b;
    int locksacquired[num];
    for(int i=0; i<num; i++){
      locksacquired[i]=-1;
    }

    int j=0;
    for(int i=0; i<num; i++){
        b=(keys[i]%Bnum)*5;
  
       // printf("The value we want to insert is %d\n", keys[i]);
       //printf("The value of b is %d\n", b);
       if(islockacquired[b]){

	continue;
      }
      else if(bucketlist[b]->snodelock.try_lock()){
	//printf("lock acquired\n");
	islockacquired[b]=true;
	locksacquired[j]=b; //keeps track of which snodes had there
			    //locks acquired
	j=j+1;
	//bucketlist[b]->snodelock.lock();
      }
      else{ //value we are trying to insert on already has its lock
	    //acquired-operation taking place
	 int g=0;
	  while(locksacquired[g]!=-1 && g<num){
	  islockacquired[locksacquired[g]]=false; //sets locks we have
						  //founsd so dar to false
	  bucketlist[locksacquired[g]]->snodelock.unlock(); //unlock
	  g=g+1;
	  }
	  //ourmutex.unlock();
	
	std::this_thread::yield();
      
      }

    
    }
    int y=0;
    while(locksacquired[y]!=-1 && y<num){
      islockacquired[locksacquired[y]]=false;
      y=y+1;
    }
    // ourmutex.unlock();
    
    for(int i=0; i<num; i++){
      results[i]=newinsert(keys[i]);
    }

    int a=0;
    while(locksacquired[a]!=-1 && a<num){
    
    
    
      bucketlist[locksacquired[a]]->snodelock.unlock(); //unlock every
							//thread being
							//worked on
							//once they
							//are finished
    
      a=a+1; 
    }
    
  }

  bool newinsert(int key){
    int b = (key % Bnum)*5;
    //printf("value we are inserting is %d\n", key);
    //  printf("bucket we are inserting into is %d\n", b);
    Node *a=create_Node(key);
    if(bucketlist[b]->head){
      Node *start=bucketlist[b]->head;
      if(key<start->value){
	a->next=start;
	bucketlist[b]->head=a;
	//printList(bucketlist[b]->head);
	//bucketlist[b]->snodelock.unlock();
	return true;
      }

      while(start->next){
	if(start->value==key){
	  //printList(bucketlist[b]->head);
	  return false;
	}
	if(start->next->value>key){
	  a->next=start->next;
	  start->next=a;
	  //printList(bucketlist[b]->head);
	  return true;

	}
	//printf("value of start is %d\n", start->value);
	start=start->next;

      }
      if(start->value==key){
	//printList(bucketlist[b]->head);
	return false;
      }
      start->next=a;
      //printList(bucketlist[b]->head);
      return true;
      
    }
    else{
      bucketlist[b]->head=a;
      //printList(bucketlist[b]->head);
      return true;
    }
  }
     
    //   return true;
    //  bool insert=true;
    
   
   
    
    //ourmutex.unlock();
      // int b= keys[i] % mynum;
      


      //  insert=singleinsert(keys[i]);
      //results[i] = insert;

      
    

   



  void remove(int* keys, bool* results, int num)
  {
    //ourmutex.lock();
    int b;
    int locksacquired[num];
    for(int i=0; i<num; i++){
      locksacquired[i]=-1;
    }

    int j=0;
    for(int i=0; i<num; i++){
      //printf("value we are removing is %d\n", b);
      b=(keys[i]%Bnum)*5;
      if(islockacquired[b]){
	continue;
      }
      else if(bucketlist[b]->snodelock.try_lock()){
	islockacquired[b]=true;
	locksacquired[j]=b; //keeps track of which snodes had there
	//locks acquired
	j=j+1;
	//bucketlist[b]->snodelock.lock();
      }
      else{
	int g=0;
	while(locksacquired[g]!=-1 && g<num){
	  islockacquired[locksacquired[g]]=false; //sets locks we have
	  //founsd so dar to false
	  bucketlist[locksacquired[g]]->snodelock.unlock(); //unlock
	  g=g+1;
	}
	//ourmutex.unlock();
	std::this_thread::yield();

      }


    }
    int y=0;
    while(locksacquired[y]!=-1 && y<num){
      islockacquired[locksacquired[y]]=false;
      y=y+1;
    }
    
    //ourmutex.unlock();
    
    for(int i=0; i<num; i++){
      results[i]=newremove(keys[i]);
     
    }
    int a=0;
    while(locksacquired[a]!=-1 && a<num){
      bucketlist[locksacquired[a]]->snodelock.unlock();
      a=a+1;
    }
    
  }
    
    /*    ourmutex.lock();
    bool ourremove=true;

    for(int i=0; i< num; i++){
      //int b= keys[i] % mynum;
      ourremove=singleremove(keys[i]);
      //printf("value of i is %d\n", i);
      //printf("value of b is %d\n", b);
      //printf("we are inserting %d\n", keys[i]);





      results[i] = ourremove;
      }*/
    // ourmutex.unlock();
    


  void lookup(int* keys, bool* results, int num) const
  {
    //  ourmutex.lock();
     
     int b;
     int locksacquired[num];
     for(int i=0; i<num; i++){
       locksacquired[i]=-1;
     }

     int j=0;
     for(int i=0; i<num; i++){
       //printf("value we are removing is %d\n", b);
       b=(keys[i]%Bnum)*5;
       if(islockacquired[b]){
	 continue;
       }
       else if(bucketlist[b]->snodelock.try_lock()){
	 islockacquired[b]=true;
	 locksacquired[j]=b; //keeps track of which snodes had there
	 //locks acquired
	 j=j+1;
	 //bucketlist[b]->snodelock.lock();
       }
       else{
	 int g=0;
	 while(locksacquired[g]!=-1 && g<num){
	   islockacquired[locksacquired[g]]=false; //sets locks we
						   //have
	   //founsd so dar to false
	   bucketlist[locksacquired[g]]->snodelock.unlock(); //unlock
	   g=g+1;
	 }
	 // ourmutex.unlock();
	 std::this_thread::yield();

       }
     }
     int y=0;
     while(locksacquired[y]!=-1 && y<num){
       islockacquired[locksacquired[y]]=false;
       y=y+1;
     }

     //ourmutex.unlock();
     for(int i=0; i<num; i++){
       results[i]=newlookup(keys[i]);

     }
     int a=0;
     while(locksacquired[a]!=-1 && a<num){
       bucketlist[locksacquired[a]]->snodelock.unlock();
       a=a+1;
     }

  }  
     /*bool ourlookup=true;
    for(int i=0; i< num; i++){
      //int b= keys[i] % mynum;
      ourlookup=singlelookup(keys[i]);

      results[i] = ourlookup;
    }
    //ourmutex.unlock();
    }*/
  
  /* shash(unsigned _buckets){
  }*/

        
          
        /// insert *key* into the appropriate linked list if it doesn't already
	/// exist; return true if the key was added successfully.

	/// remove *key* from the appropriate list if it was present; return true
	/// if the key was removed successfully.
	bool newremove(int key)
	{
	  int b = (key % Bnum)*5;

	  
	  /*  while(!bucketlist[b]->snodelock.try_lock()){
	    std::this_thread::yield();
	    }*/
	  //bucketlist[b]->snodelock.lock();
	  // printf("value we are removing is %d\n", key);
	  if(bucketlist[b]->head){
	    Node* currNode=bucketlist[b]->head;
	    if(currNode->value==key){
	      if(currNode->next){
		bucketlist[b]->head=currNode->next;
	      
	      }
	      else{
		bucketlist[b]->head=NULL;
	      }
	      //  printList(bucketlist[b]->head);
	      //  bucketlist[b]->snodelock.unlock();
	      // printList(bucketlist[b]->head);
	      return true;
	    }
	    while(currNode->next){
	      if(currNode->value>key){
		//printlist(bucketlist[b]->head);
		//bucketlist[b]->snodelock.unlock();
		//printList(bucketlist[b]->head);
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
		//bucketlist[b]->snodelock.unlock();
		//   printList(bucketlist[b]->head);
		return true;
	      }
	      // printf("value of currNode is %d\n", currNode->value);
	      currNode=currNode->next;
	    }

	    if(currNode->value==key){
	      currNode=NULL;
	      // printList(bucketlist[b]->head);
	      // bucketlist[b]->snodelock.unlock();
	      //printList(bucketlist[b]->head);
	      return true;
	    }
	    //printlist(bucketlist[b]->head);
	    //bucketlist[b]->snodelock.unlock();
	    //printList(bucketlist[b]->head);
	    return false;
	  }

	  else{
	    //printList(bucketlist[b]->head);
	    //bucketlist[b]->snodelock.unlock();
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
	bool newlookup(int key) const
	{

	  
	  //bool lookup=true;
	  int b = (key % Bnum)*5;
	  /*while(!bucketlist[b]->snodelock.try_lock()){
	    std::this_thread::yield();
	    }*/
	  //bucketlist[b]->snodelock.lock();
	  Node* curr=bucketlist[b]->head;
	  while(curr){
	    /*if(curr->value>key){
	      // bucketlist[b]->snodelock.unlock();
	      return false;
	      }*/
	    if(curr->value==key){
	      //bucketlist[b]->snodelock.unlock();
	      return true;
	    }
	    curr=curr->next;
	  }
	  
	  //bucketlist[b]->snodelock.unlock();
	  return false;
	  
	  //return bucketlist[b].lookup(key);
	  
	  
	}

	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.

	//This refers to the number of buckets not the total number of
	//elements.
  
	size_t getSize() const
	{
	  return Bnum+((Bnum-1)*4); 
	}

	//This refers to the number of elements in a bucket, not the sentinel node.
	size_t getBucketSize(size_t bucket) const
	{
	  int bucketpos=static_cast<int>(bucket);
	  if(bucketpos>Bnum-1){
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
	  if(bucketpos>Bnum-1){
	    return -1;
	  }
	  Node* start=bucketlist[(bucketpos)*5]->head;
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
    
