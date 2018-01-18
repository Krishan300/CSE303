#include  <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "support.h"

/*
 * sed_file() - modify lines of filename based on pattern, and print result
 *              to STDOUT
 */

extern char *strdup(const char *s);

//confirm if search term is empty 
int isempty(char *lookthrough){
  for(int i=0; i<strlen(lookthrough); i++){
    if(!isspace(lookthrough[i])){
	return 0;

      }
  }
      return 1;
      

}
void search_file(char* filename, char* find, char* replace){
  FILE *fp; //=fopen(filename, "r");
  if(!filename)
  {
    // printf("reached here\n");
      fp=stdin;
    }
    else{
    fp=fopen(filename, "r");

     }
  if(fp){
    int c;
    while((c=fgetc(fp))!=EOF)
      {

	if((c==' ') || (c=='\n') || (c=='\t')){
	  printf("%c", c);

	}
       
	else if ((isdigit(c) || isalpha(c) || ispunct(c)))
	  {
	    char input[1024];
	    memset(input, '\0', 1024);
	    int i=0;
	    while(isdigit(c) || isalpha(c) || ispunct(c)){
	      char a=(char)c;
	      input[i]=a;
	      i=i+1;
	      c=fgetc(fp);
	     }
	    input[i+1]='\0';
	    ungetc(c,fp); //get each line from file
             
	    //if search string is haystack
	    if(strstr(input, find)){
	 
	      /*      char buffer[1024];
	     
       		
		  }*/
		
	
	     int tokenum=strlen(input);
	     
	      char containssplit[tokenum][1024];
	      for(int i=0; i<tokenum; i++)
		{
		  char substring[sizeof(find)];
		  int ss=sizeof(find);
		  memset(substring, '\0', ss);
		  memcpy(substring, &input[i], strlen(find));
		 
		  strcpy(containssplit[i], substring);

	
		 
		 



		}

	      int i=0;
	  
	     
	      while (i<tokenum){
		 if(strcmp(containssplit[i], find)==0)
		 {
		   printf("%s", replace);
		   /*  for (; i<i+strlen(find); i++)

			
	              }*/
		   // i=i+1;
		   i=i+strlen(find);
		 }
	
	
	

		 //else{
	      /*	  else if(nohit==1){
		
		    for (; i < (i+strlen(find)); i++ )
		     {
	
		       if(i==tokenum){
	
	
	
	
	
			 break;
	
		       }
		       if(strcmp(containssplit[i], find)==0)
			 {
			
			  
			  
			 }
		       
		     }
		     i=i+1;
		   
			  
		     }*/

		 else {
		   /*  if(strcmp(containssplit[i+1], find)==0)
		     {
		     printf("%c", containssplit[i][0]);
		     i=i+1;
		      }
		   else if (strcmp(containssplit[i+2], find)==0){
		      printf("%c", containssplit[i][0]);
		
		      i=i+1;
		      
		      }*/

		 
		   // else{
		   //print first char in token if not equal
		     printf("%c", containssplit[i][0]);
		     i=i+1;
		     //i=i+strlen(find);
	
	
	
	
	
		     //}

		 }
	

		 
			  
	      


		 
	      }
	    }
	    else {
	      //if search term is not in string, just print it
	      printf("%s", input);

	    }

	    memset(input, '\0', i);
	  }



	else{
	  printf("%c", c);
	}


      }
    fclose(fp); 
  }
  else{
    printf("sed: can't read  %s: No such file or directory\n", filename);
    exit(0);

  }
  
  
    
    


  

}
  

/*void printarr(char **poiray, int size){
  

  }*/
void sed_file(char *filename, char *pattern) {
    /* TODO: Complete this function */
    /*   const char delimiter[1]="/";
     char *token;
 
     char alltoke[1024][2048];
 
 
     int i=0;
     token=strtok(pattern, delimiter);
     while(token!=NULL){
 
 
 
 
       strcpy(alltoke[i],token);
 
       i=i+1;
       token=strtok(NULL, delimiter);
       // printf("%s\n", token);
     }

      if(i>4){
	 printf("Error: Too many arguments\n");
	   exit(0);
      }
       
 





     if(i<4){
       printf("Error: too few arguments\n");
       exit(0);
       }


     if(strcmp(alltoke[0], "s")==0){
       if(strcmp(alltoke[3], "g")==0){
	 search_file(filename, alltoke[1], alltoke[2]);
       }
       else {
	 printf("Error: The final parameter must equal g\n");
	 exit(0);
       }
     }*/
      char *dest=(char*)malloc(sizeof(char)*2048);
      // char dest[2048];
      //int size=sizeof(char*);
      //int destsize=sizeof(char);
      memset(dest, '\0', 2048);
      if(pattern[0]=='s'){
	if(pattern[strlen(pattern)-1]=='g'){
	  if(pattern[1]=='/'){
	    if(pattern[strlen(pattern)-2]=='/'){
	      strncpy(dest, &pattern[2], strlen(pattern)-4);
	      int slashcount=0;
	      int location=0;
	      for(int i=0; i<strlen(dest); i++){
		if(dest[i]=='/'){
		  slashcount=slashcount+1;
		  location=i;
		}
	
		
		

		
	      }
	      //printf("%d\n", slashcount);
	      if(slashcount!=1){
		printf("Error: To many /'s\n");
		exit(0);
	      }
	      char *find=(char*)malloc(sizeof(char)*2048);
	      
	      // char find[2048];
              memset(find, '\0', 2048);	      
	      strncpy(find, dest, strlen(dest)-(strlen(dest)-location));
	      if(isempty(find)){
		printf("The word to find and replace must have a value\n");
		exit(0);
		}
	    	      
	      char *replace=(char*)malloc(sizeof(char)*2048);
	      memset(replace, '\0', 2048);
	      strcpy(replace, &dest[location+1]);
	    
	      search_file(filename,find,replace);
	      free(replace);
	      free(find);
	      free(dest);
	    }
	    else{
	      printf("Error: Second to last char in pattern is not /' \n");
	      exit(0);
	    }
	  }
	  else {
	    printf("Error: Second char in pattern is not /' \n");
	    exit(0);
	  }
	}
	else{
	  printf("Error: Last char in pattern is not g\n");
	  exit(0);
	}
      }
      else{
	printf("Error: First char in pattern is not s\n");
	exit(0);
      }
	    
	
	

	      
	
	
	

	
	
	
	

    
    


     //int start=0;

	/*  while(alltoke[start]){
	  // for(int i=0; i<1024; i++){
	  // free(alltoke[start][i]);
	  // }
	  free(alltoke[start]);
	 start=start+1;
	}
	free(alltoke);*/
}
    /* for(int j=0; j<i; j++){
      printf("%s\n", alltoke[j]);
      }*/
   // token=strtok(patterm, delimiter);
  
   
  
  















	
      // printf("%s\n", input);
	
	//printarr(input, i);




      


/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print the contents of FILE to STDOUT\n");
    printf("With no FILE, read standard input\n");
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

    /* TODO: fix this invocation */
    sed_file(argv[optind+1], argv[optind]);
    // search_file("text", "the", "boy");
}
