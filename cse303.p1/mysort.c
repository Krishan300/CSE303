#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "support.h"

/*
 * sort_file() - read a file, sort its lines, and output them.  reverse and
 *               unique parameters are booleans to affect how the lines are
 *               sorted, and which lines are output.
 */
extern char *strdup(const char *s);

/*int regularsort(const void *a, const void *b){
  //const char *str1= *(const char **) a;
  //const char *str2= *(const char **) b;

  return wrapper(a, b);
  
  }*/

int regularsort(const void *a, const void *b){
  const char *str1=*(const char**)a;
  const char *str2=*(const char**)b;
  return strcmp(str1, str2);
}

int cmpfunc(const void *a, const void *b){

  //const char* str1=*(const char**) a;
  //const char* str2=*(const char**) b;
  /*const char *str1=*(const char **) a;
  const char *str2=*(const char **) b;
  return strcmp(str1, str2)*-1;*/
  return -1*regularsort(a,b);
}

void sort_file(char *filename, int unique, int reverse) {
  char **filearray=(char**)malloc(1000000*sizeof(char*));
  
  memset(filearray,0,1000000*sizeof(char*));
  char input[1024];
  FILE* fp=fopen(filename, "r");
  int startstr=0;
  if(fp==NULL){
    printf("sort: open failed: %s: No such file or directory\n", filename);
    exit(0);
  }
  // printf("%s", "reached here");
  while(fgets(input, 1024, fp)){
   
   
    filearray[startstr]=strdup(input);
    startstr=startstr+1;
  }
  


  if(reverse==1){
    qsort(filearray, startstr, sizeof(char*),cmpfunc);
  }
  else {
   
    qsort(filearray, startstr, sizeof(char*), regularsort);
    }

  
  // qsort(filearray, 1000000, sizeof(char*), regularsort);
  if(unique){
   
   
   
    
    for (int i=0; i<1000000;i++)
      {
	if(!filearray[i+1]){
	  printf("%s", filearray[i]);
	  break;
	}
	if(strcmp(filearray[i], filearray[i+1])==0){
	  //seenalready=1;
	  continue;
	}
	else {
	  if(filearray[i]){
	    printf("%s", filearray[i]);
	  }
	}
	   
      }

  }

  else{
    for(int i=0; i<1000000; i++){
      if(filearray[i])
	{
	  printf("%s", filearray[i]);
	}
    }
  }
  for(int i=0; i<1000000; i++){
    free(filearray[i]);
    
  }
  free(filearray);
  fclose(fp);
    //} 
    /* TODO: Complete this function */
    /* Note: you will probably need to implement some other functions */
    /*if(unique){
    //implement sort that ignores duplicates
  }
  if(reverse){
  c*/
    //call sort that reverses order
  
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [OPTIONS] FILE\n", progname);
    printf("Sort the lines of FILE and print them to STDOUT\n");
    printf("  -r    sort in reverse\n");
    printf("  -u    only print unique lines\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;
    int reverse=0;
    int unique=0;
    /* ensure the student name is filled out */
    check_student(argv[0]);

    /* parse the command-line options.  They are 'r' for reversing the */
    /* output, and 'u' for only printing unique strings.  'h' is also */
    /* supported. */
    /* TODO: parse the arguments correctly */
    while ((opt = getopt(argc, argv, "hru")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
	  case 'r': reverse=1; break;
	  case 'u': unique=1;  break; 
        }
    }

    /* TODO: fix this invocation */
    // sort_file(argv[optind], 0, 0);
    //printf("%d", reverse);
    if(argc==1){
      puts("Need arguments");
      exit(0);
    }
    // printf("%s\n", argv[2]);
    sort_file(argv[optind],unique,reverse);
}
