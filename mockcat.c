#include <stdio.h>

int fileprinter(FILE* fp, char *file){
  fp=fopen(file,"r");
  int c;
  if (fp){
    while ((c=getc(fp))!=EOF)
      putchar(c);
    fclose(fp);
    return 1;
  }
  else {
    return 0;
  }
}

void fileopener(char* file){
  FILE *fp;
  int c;
  if (fileprinter(fp, file) == 0) {
      printf("cat: %s: No such file or directory\n",file);
    }
      // sleep(0);
    //fp=fopen(file, "r");
    // if (fp){
    // while ((c=getc(fp))!=EOF)
    //	putchar(c);
    //  fclose(fp);
    
  
 }



  
int main(int argc, char *argv[]){
  char input[2048];
  FILE *fp;
  if(argc==1){
    while (1==1) {
      fgets(input, sizeof(input), stdin);
     
      printf("%s", input);
      
      }
    // else {
    // fileopener(argv[1]);
    // }
  }
  else {
    int i;
    for (i=1; i<argc; i=i+1){
        
	fileopener(argv[i]);
	i++;
      }
  }
  
  // }
  // else{
  //fileopener(argv[1]);
  //}
  
  return 0;
}
