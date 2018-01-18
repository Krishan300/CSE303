#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "support.h"

/*
 * grep_file() - display all lines of filename that contain searchstr
 */
void grep_file(char *filename, char *searchstr) {
    /* TODO: Complete this function */
  char input[1024];
  if(!searchstr){
    printf("Error: No search string provided\n");
    exit(0);
  }
  
  if(filename){
    //char input[1024];
    FILE *fp=fopen(filename, "r");
    if(!fp){
      printf("grep: %s: No such file or directory\n", filename);
      exit(0);

    }
    while(fgets(input, 1024, fp)){
      if(strstr(input, searchstr)){
	printf("%s", input);
	}

    }
    free(fp);
   }
   else{
     while(fgets(input, 1024, stdin)){
       if(strstr(input, searchstr)){
	 printf("%s", input);
       }
       
     }
     // exit(0);
    }
    
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s STR FILE\n", progname);
    printf("Print to STDOUT the lines of FILE that contain STR\n");
    printf("With no FILE, read standard input\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;
    // char* searchstring;
    //char* filename;
    
    /*    if(argv[1]){
      searchstring=argv[1];
    }

        if(argv[2]){
      filename=argv[2];
      }*/
    /* run a student name check */
    check_student(argv[0]);

    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage. */
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
        }
    }

    /* make sure we have two more parameters */
    if (optind == argc) {
        printf("Error: not enough arguments\n");
        exit(1);
	}
    //  printf("%d", optind);
    //printf("%s", argv[optind]);
    /* TODO: fix this invocation */
    //grep_file( "text", "pie");
     //printf("%s", argv[1]);
     /*     if(argc<0){
       exit(0);
       }*/
    //  printf("%s\n", searchstring);
    // printf("%s\n", filename);
     //grep_file(optind < argc ? argv[optind]: searchstring,
     //filename);
    
    //  if (!argv[optind+1]){
    // grep_file(NULL, argv[optind]);
    // }
    /*else if (argc==4){
      grep_file(
      }*/
    //else{
     grep_file(argv[optind+1], argv[optind]);
     // }
    
}
