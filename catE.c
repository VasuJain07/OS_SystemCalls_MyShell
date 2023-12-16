#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
 
int main(int argc, char *argv[]) {
  FILE *file;
  int chr;

  char p[1024];
  memcpy(p,argv[1],strlen(argv[1]));
  strcpy(&p[strlen(argv[1])],"/");
  strcpy(&p[strlen(argv[1])+1],argv[2]);
 
  if((file = fopen(p, "r")) == NULL) {
    printf("%s\n",strerror(errno));
  }
  while((chr = getc(file)) != EOF){
    if(chr=='\n'){printf("$");}
    printf("%c", chr);
  }
  printf("\n");
  fclose(file);
  exit(0);
}