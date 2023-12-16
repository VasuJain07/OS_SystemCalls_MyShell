#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char* argv[]){
	// char *p="//home//vasujain//Desktop//workspace//hello";
	char p[1024];
	memcpy(p,argv[1],strlen(argv[1]));
	strcpy(&p[strlen(argv[1])],"/");
	strcpy(&p[strlen(argv[1])+1],argv[2]);
	mkdir(p,0777);
	printf("%s\n", strerror(errno));
}