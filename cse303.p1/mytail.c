#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include <string.h>


/*struct circbuffer {
  int head;
  int tail;
  char **buffer;
  int length;
  };*/


/*char* strdup(const char* s){
  size_t slen=strlen(s);
  char* result = malloc(slen + 1);
  if(result == NULL)
    {
      return NULL;

    }

  memcpy(result, s, slen+1);
  return result;


  }*/


/*
 * tail_file() - display the last numlines lines of a file or stdin
 */
extern char *strdup(const char *s);
void tail_file(char *filename, int numlines) {
  /* TODO: Complete this function */
  //  char errormessage[2000];
  //char *errorpart="cannot open for reading";
  // char *errormessage=malloc(sizeof(filename)+sizeof(errorpart));
	       //char errormessage[1054];
  /*strcpy(errormessage, "tail: cannot open ");
  
  strcat(errormessage, filename);
  strcat(errormessage, " for reading");*/
  if(numlines==0){
    exit(0);

  }
  if(numlines<0){
    numlines=numlines*-1;
  }
  char input[1024];
  //allocate as much memory for each string that needs to be printed
  char **circray=(char**)malloc(numlines * sizeof(char*));
  //set array so no values are undefined
  memset(circray, 0, sizeof(char*)*numlines);
  int tail=0;
  if(filename)
    {
      
      char errormessage[1054];
      strcpy(errormessage, "tail: cannot open ");
      strcat(errormessage, filename);
      strcat(errormessage, " for reading");
      //char **circray=(char**) malloc(numlines * sizeof(char*));
      //int tail=0;
      FILE *thisfile=fopen(filename,"r");
       if(!thisfile)
	{
	   
          perror(errormessage);
	
	  exit(0);
	  }

      while(fgets(input, 1024, thisfile)) {
       
       	if(circray[tail]){
	  //if part of array is allocated, free it before reallocating
	  free(circray[tail]);
	  
	  // circray[tail]=(char*)realloc(circray[tail], sizeof(char*));

	  }
	 //set position in array to input string 
	 circray[tail]=strdup(input);
	//	memcpy(circray[tail], input, 1024);
    
	tail=(tail+1)%numlines;
      }
      fclose(thisfile);
    }
  else{
    //char input[1024];
    //same process, but reading from stdin
    while(fgets(input, 1024, stdin)){
      //memcpy(circray[tail], input, 1024);
      if(circray[tail]){
	free(circray[tail]);
      }
      circray[tail]=strdup(input);
      tail=(tail+1)%numlines;

    }


  }
      for(int i=tail; i<numlines;i++)
	{
         
	  if(circray[i]){
         printf("%s", circray[i]);
	  }
    }
   for(int i=0; i<tail; i++){
     if(circray[i]){
      printf("%s", circray[i]);
      }

   }

   /*   char **a;
   while(circray[i+1])
     {
       free(circray[i]);
       i=i+1;
       }
   for (a=circray; *a; a++){
     free(*a);
   }*/
 
   for(int i=0; i< numlines;i++){
     free(circray[i]);
   }
   free(circray);
   
}
      
  



      






/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print the last 10 lines  of FILE to STDOUT\n");
    printf("With no FILE, read from STDIN\n");
    printf("  -nK    print the last K lines instead of the last 10\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;
    int numlines=10;

    /* run a student name check */
    check_student(argv[0]);

    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage, */
    /* and the parametered 'n' option, for getting the number of lines. */
    /* TODO: parse the arguments correctly */
    while ((opt = getopt(argc, argv, "hn:")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;

	    //case 'n': numlines=atoi(optarg); break;
	  case 'n': numlines=atoi(optarg); break;
        }
    }

    /* TODO: fix this invocation */
    //tail_file("text",4);
    
    //
    
    
    
     
     tail_file(optind < argc ? argv[optind]:  NULL, numlines);
    
    
}
