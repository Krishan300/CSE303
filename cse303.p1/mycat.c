#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"
//heyaddedcommen
/*
 * cat_file() - display the contents of a file by reading it, line by line
 */
void cat_file (char *filename) {
    /* TODO: Complete this function */
  //FILE *file;
  //char input[1024];
  if(!filename){
    //printf("%s", "there is no filename");
    char input[1024];
    while(fgets(input, 1024, stdin))
      {
	fputs(input, stdout);
      }
  }
  else
    {
      FILE *file=fopen(filename, "r");
      
    
  //FILE *file=fopen(filename, "r");
     char errormessage[1027];
     strcpy(errormessage, "cat: ");
  //  printf("%i", fileno(file));
     strcat(errormessage, filename);
  // char input[1024];
  
      char input[1024];
      if(file){  
	while (fgets(input,1024,file))
	 {
	   fputs(input, stdout);
	 }
	fclose(file);
      }
      else{
	perror(errormessage);
	exit(0);
      }
    }
  // int c;
  /*if (file!=NULL) {
     while ((c=fgetc(file))!=EOF)
    {
	putchar(c);
    }
    fclose(file);
   
  }
  else{
    perror(errormessage);
    exit(0);
    }*/
  
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print the contents of FILE to STDOUT\n");
    printf("With no FILE, read from STDIN\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
  
  // char input[1024];
  /* if (argc==1){
     while (1==1){
      char input[1024];
      if(fgets(input, 1024, stdin)){
         fputs(input, stdout);
      }
      else{
	exit(0);
      }
    }
    }*/
    
    long opt;
    
    /* run a student name check */
    check_student(argv[0]);

    // cat_file(argv[1]); 

    

    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage. */
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
        }
    }

    /* optind is a global indicating the first unparsed argument */
    /* If we have options remaining, it must mean we have a file name */
    /* Note that getopt rearranges the entries in argv */
    cat_file(optind < argc ? argv[optind] : NULL);

}
