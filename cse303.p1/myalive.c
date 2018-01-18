#include <getopt.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "support.h"

/*
 * alive() - install some signal handlers, set an alarm, and wait...
 */

volatile sig_atomic_t alarmtriggered=1;
volatile sig_atomic_t interrupttriggered=0;

//void inthandler(int sig);
void inthandler(int sig){
  //interrupttriggered(0);
  interrupttriggered=1;
  signal(sig, inthandler);
  }

void alarmhandler(int sig){
  alarmtriggered=0;
  //signal(sig, alarmhandler);
  // exit(0);
   // signal(sig, alarmhandler);

  // exit(0);
  signal(SIGALRM, alarmhandler);
}

void alive(void) {
    /* TODO: Complete this function */
    /* Note: you will probably need to implement some other functions */
  
 
    struct timeval initialtime, endtime;
    gettimeofday(&initialtime, NULL);
    
    signal(SIGALRM, alarmhandler);
   
    signal(SIGINT, inthandler);    
   
    alarm(10);
    while(alarmtriggered){
    
    

      /*   if(alarmtriggered==0){
	break;
	
	}*/

      //print no whenever sigint received
      if(interrupttriggered==1){
	interrupttriggered=0;
	printf("%s\n","no");
	  
	}
	//raise(SIGALRM);
	
	
	
      
     }
    //printf("%d\n", interrupttriggered);
    // printf("%d\n", alarmtriggered);

    //subtract end from start time
    gettimeofday(&endtime, NULL);
    printf("%ld\n", (endtime.tv_sec-initialtime.tv_sec));
    exit(0);
      
    //}
    // exit(0);
   
   
   

	

}

















  

/*
void inthandler(int signum){
  fputs("no",stdout);
  }*/

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s\n", progname);
    printf("Swallow SIGINT, exit on SIGALARM\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;
    alarm(10);

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
    alive();
}
