#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdio.h>
#include <netdb.h>
#include <ctype.h>
#include "support.h"

/*
 * host() - Print the hostname of the machine on which this program is
 *          running, formatted a few different ways
 */
void host(void) {
  char hostname[255];
  hostname[254]='\0';
  // hostname[127]='\0';
  //hostname[strlen(hostname)-1]='\0';
  gethostname(hostname, 128);
  // hostname[strlen(hostname)-1]='\0';
  
  printf("Hostname for machine: %s\n", hostname);
  char upperhostname[255];
  memset(upperhostname,'\0', 255);
  char mixedhostname[255];
  memset(mixedhostname, '\0', 255);
  char backwardhostname[255];
  memset(backwardhostname, '\0', 255);
  //  int i=0;
  //while(hostname[i]){
  for (int i=0; i<strlen(hostname); i++){
    // printf("%c\n", hostname[i]);
    if(i%2!=0){
       mixedhostname[i]=hostname[i];
      // putc(hostname[i], stdout);
    }
    else{
       mixedhostname[i]=toupper(hostname[i]);
      // putc(toupper(hostname[i]);
    }
       backwardhostname[(strlen(hostname)-1)-i]=hostname[i];
	// printf((strlen(hostname)-1)-i), stdout);
	//printf("%c", (toupper(hostname[i])));
    upperhostname[i]=toupper(hostname[i]);
    //i=i+1;
  }

  //upperhostname[strlen(upperhostname)]='\0';
  //backwardhostname[strlen(backwardhostname)]='\0'; 
  //mixedhostname[strlen(mixedhostname)]='\0';
  printf("Upper case hostname for machine: %s\n", upperhostname);
  printf("Mixed case hostname for machine: %s\n", mixedhostname);
  printf("Backward case hostname for machine: %s\n", backwardhostname);
 
    /* TODO: Complete this function */
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s\n", progname);
    printf("Display the hostname of the machine\n");
    printf("The name will be displayed four ways, in the following order, on "
           "four lines:\n");
    printf("  all lowercase\n");
    printf("  ALL UPPERCASE\n");
    printf("  mIxEd LoWeRaNdUpPeR\n");
    printf("  emantsoh (i.e., reversed)\n");
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

    /* no need to look at arguments before calling the code */
    host();
}
