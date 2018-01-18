#pragma once
#include <iostream>
#include <iomanip>
#include <algorithm>    // std::max
using namespace std;
#include <mutex>



/// TODO: complete this implementation of a thread-safe (concurrent) AVL
///       tree of integers, implemented as a set of Node objects.
///       In addition, the API now allows for multiple insertions on each
///       operation.
///       Less than goes to the left. Greater than goes to the right.
class tree
{
//This is for testing purposes. Do not access your Node directly.
	size_t size = 0;
	mutable std::mutex mtx;  


public:
	struct Node
	{
		public:
			int value;
			Node* left;
			Node* right;
			//Node* parent;
			int height = 0;
	};
	Node* head;



public:
	tree(int)
	: head(NULL)
	{}


	Node* inserthelper(Node* root, int data){
		//printf(" helper %d\n",data);
		
		if(root == NULL)
		{
				//*result = true;
				
				//result = true;
				size++;
				root = new Node;
				root->value = data;
				root->left = NULL;
				root->right = NULL;
				root->height = 0;
			
			return root;
		}
		else if(data < root->value)
		{
			root->left = inserthelper(root->left, data);
			//printf("call\n");

			
		}
		else if(data > root->value)
		{
			root->right = inserthelper(root->right,data);
			//printf("call\n" );


			
		}
		else if(root->value == data)
		{
			//results = false;
			return root;
		}
		//int height = findHeight(root);

		return root= balance(root);

	}


	Node *balance(Node *root)
	{
		int balance = balanceFactor(root);
	    if (balance == 2)
	    {
	        if (balanceFactor (root->left) > 0)
	        {
	            root = llrotation(root);//left left
	        }
	        else
	        {
	            root = lrrotation(root);//left right
	        }
	    }
	    else if (balance == -2)
	    {
	        if (balanceFactor (root->right) > 0)
	            root = rlrotation (root);//right left
	        else
	            root = rrrotation (root);// right right
	    }
	    return root;
	}



	Node *llrotation(Node *root)
	{
		Node *a = root->left;
		root->left = a->right;
		a->right = root;
		return a;
	}


	Node *rrrotation(Node *root)
	{
		Node *a = root->right;
		root->right = a->left;
		a->left = root;

		return a;
	}

	Node *lrrotation(Node *root)
	{
		Node *a = root->left;
		root->left = rrrotation(a);
		return llrotation(root);
	}

	Node *rlrotation(Node *root)
	{
		Node *a = root->right;
		root->right = llrotation(a);
		return rrrotation(root);
	}


	int findHeight(Node* node)
	{
	// 	if(node == NULL)
// 		{
// 			return -1;
// 		}
// 		else
// 		{
// 			return node->height;
// 		}
		int height = 0;
		if(node != NULL)
		{
			int leftHeight = findHeight(node->left);
			int rightHeight = findHeight(node->right);
			int max = std::max(leftHeight, rightHeight);
			height = max +1;
		}
		return height;
	}

	int balanceFactor(Node* head)
	{
		int balanceFactor = findHeight(head->left)-findHeight(head->right);
		//printf("BF: %d",balanceFactor);
		return balanceFactor;
	}


	/// insert /num/ values from /data/ array into the tree, and return the
	/// success/failure of each insert in /results/ array.
	void insert(int* data, bool* results, int num)
	{
		// printf("insert start: ");
		//inserthelper(head, data);
		// printf("insert  %d\n", data[0]);
		//mtx.lock();
		// for(int i=0; i<num; i++)
// 		{
			mtx.lock();
			//int insertvalue=data[i];
			//bool retval=inserthelper(insertvalue);
			//printf("insert  %d\n", data[0]);
			head = inserthelper(head, data[0]);
			//printf("result  %s\n", results[i]);
			
			results[0]=true;
			//display(head, 1);
			//printf("insert over\n");
			mtx.unlock();
			//printf("result  %d\n", getSize());
// 		}
		//mtx.unlock();
		//postorder(head);
	}


// 
// 	void display(Node *ptr, int level)
// 	{
// 	    int i;
// 	    if (ptr!=NULL)
// 	    {
// 	        display(ptr->right, level + 1);
// 	        printf("\n");
// 	        if (ptr == head)
// 	        cout<<"Root -> ";
// 	        // int a = getElement(1,head);
// // 			printf("get elem: %d\n",a); // getElement(1,head));
// 	        for (i = 0; i < level && ptr != head; i++)
// 	            cout<<"        ";
// 	        cout<<ptr->value;
// 	        display(ptr->left, level + 1);
// 	    }
// 	}

	Node *removehelper(Node *root, int data)
	{
		//printf(" helper %d\n",data);
		if(root == NULL)
		{
			
			return root;
		}
		else if(data < root->value)
		{
			root->left = removehelper(root->left, data);
			//printf("call\n");

			
		}
		else if(data > root->value)
		{
			root->right = removehelper(root->right,data);
			//printf("call\n" );


			
		}
		else if(root->value == data)
		{
			size--;
			if(root->left == NULL)
			{
				Node *node = root->left;
				delete root;
				return node;
			}
			else if(root->right == NULL)
			{
				Node *node = root->right;
				delete root;
				return node;
			}
			else if (root->left != NULL && root->right != NULL)
			{
				 Node* temp = root->right;
				 while(temp -> left != NULL)
				 {
				 	temp = temp->left;
				 }
				 
           		 root->value = temp->value;
            	 root->right = removehelper(root->right, temp->value);
			}
			
			root = balance(root);
			//results = false;
			//return root;
		}
		
		
		//int height = findHeight(root);

		return root;//node= balance(root);

	}
	

	


	/// remove *data* from the list if it was present; return true if the data
	/// was removed successfully.
	void remove(int* data, bool* results, int num)
	{
		mtx.lock();
		// for(int i=0; i<num; i++)
// 		{
			//mtx.lock();
			//printf("remove value: %d\n", data[i]);
			//display(head,1);
			head = removehelper(head, data[0]);
			//printf("after remove\n");
			 //display(head,1);
			//mtx.unlock();
		//}
		mtx.unlock();
	}
	/// return true if *data* is present in the list, false otherwise
	void lookup(int* data, bool* results, int num) //const
	{
		mtx.lock();
		// for(int i=0; i<num; i++)
// 		{
			//results[i] = false;
			//mtx.lock();
			results[0] = lookupHelper(head, data[0]);
			//mtx.unlock();
		//}
		mtx.unlock();
		
		

	}
	
	bool lookupHelper(Node *head, int data)
	{
		
			Node* a = head;
			while(a!=NULL){
				if(a->value < data){
					a = a->right;
				}
				else if(a->value > data){
					a = a->left;
				}
				else if(a->value == data){
					//printf("success\n");
					return true;
				}
			}
			//printf("false\n");
			return false;
	}

	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.

	//Total number of elements in the tree
	size_t getSize() const
	{
		return size;
	}

	int getElement(size_t idx) //const
	{

		return getElement(idx, head);

  
	}

	

	//These functions need to exist, they do not need to do anyting
	size_t getBucketSize() const
	{
		return 0;
	}
	int getElement(size_t bucket, size_t idx) const
	{
		return 0;
	}


int getnode(Node *head)
{
	 if (head=NULL)
	 {
		  return 0;
	 }
	 else
	 {
	  	return 1+ getnode(head->left) + getnode(head->right);
	 }
}

private:
	//Returns the idx'th element from the tree assuming an inorder traversal.
	int getElement(size_t idx, Node* at) //const
	{
		//int result = 0;
		//return 0;
		//mtx.lock();
		int value = 0;
		if(at == NULL)
		{
			return -1;
		}
		int lNodes = getnode(at->left);
		if(lNodes==(int)idx)
		{
			
			return at->value;
		}
		else if(idx<lNodes)
		{
			value = getElement(idx, at->left);
		}
		else if(idx>lNodes)
		{
			value = getElement(idx-lNodes,at->right);
		}
		else if(idx>getnode(at))
		{
			return -1;
		}
		//mtx.unlock();

		return value;
		//return 0;
		
	}
};
