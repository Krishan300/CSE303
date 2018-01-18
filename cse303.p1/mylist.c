#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "support.h"

/*
 * list_task() - read from stdin, determine the appropriate behavior, and
 *               perform it.
 */
 
 typedef struct  {
  int data;
  struct Node* Link;
 } Node;

//struct Node Head;
//Node* head=NULL;
//head->Data=NULL;
//head->link=NULL;
void list_task() {
  /*  struct Node* tail=malloc(sizeof(Node*));
  Node* head=tail;
  char input[1024];
  while(fgets(input, 1024, stdin)){
    if(input[0]=='i'){
       printf("success\n");
      if(!tail->data){
	tail->data=(input[2]-'0');
        tail->Link=(malloc(sizeof(Node*)));
        tail=tail->Link;
      }
      }*/
    /* if(strcmp(input, "i")==0){
      struct Node* newnode=malloc(sizeof(Node));
      newnode->Link=NULL;
      printf("%d", input[2]);
      newnode->data=(input[2]-'0');
      }
      
  
     TODO: Complete this function 
  if(strcmp(instruction, "i")==0){
     Node *head=(Node*)malloc(sizeof(Node*));
    temp->data=data;
    temp->Link=head;
    
    }
  //  }
   while(temp->Link!=NULL){
    printf("%i\n", temp->data);
    
    }*/
}
//}
    
  

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s\n", progname);
    printf("Run an interactive list manipulation program\n");
    printf("Commands: [i]insert, [r]emove, [p]rint, e[x]it\n");
    printf("  (Commands require an integer argument)\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;

    /* run a student name check */
    check_student(argv[0]);

    /*
     * parse the command-line options.  For this program, we only support the
     * parameterless 'h' option, for getting help on program usage.
     */
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
	    //case 'i':
	  
        }
    }

    //list_task(argv[optind], argv[optind+1]);
    /* run the list program */
    list_task();
    
}
