#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char* argv[]){
	char p[1024];
	memcpy(p,argv[1],strlen(argv[1]));
	strcpy(&p[strlen(argv[1])],"/");
	strcpy(&p[strlen(argv[1])+1],argv[2]);
	remove(p);
	printf("%s\n", strerror(errno));
}