#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "support.h"

/*
 * wc_file() - count characters, words, and lines
 */
void wc_file(char *filename) {
  int isword=0;
  int wc=0;
  int lc=0;
  int bc=0;
  FILE *fp;
  char errormessage[1028];
  strcpy(errormessage, "wc: ");
  strcat(errormessage, filename);
  fp=fopen(filename, "r");
  if (fp)
    {
      int c;
      while ((c= fgetc(fp))!=EOF)
 	{
	  bc=bc+1;
	  if((c==' ') || (c=='\n') || (c=='\t')){
	    isword=0;
	  }
	  if ( (isword==0) && (isdigit(c) || isalpha(c)))
	    {
              wc=wc+1;
	      isword=1;
	    }
	  if ( (c=='\n'))
	   {
	     lc=lc+1;
	   }

	}
      printf("%d %d %d %s\n", lc, wc, bc,filename);

    }
  else
    {
      perror(errormessage);

    }
  
    /* TODO: Complete this function */
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print newline, word, and byte counts for FILE\n");
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

    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage. */
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
        }
    }

    /* error if we don't have a file, else call wc_file */
    if (argc != 2) {
        printf("Error: no file given\n");
        exit(1);
    }
    wc_file(argv[1]);
}
