#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <ctype.h>

void curdir(){
	char cwd[1024]; 
	memset(cwd,'\0',sizeof(cwd));
    getcwd(cwd, sizeof(cwd)); 
    printf("Dir: %s", cwd);
    printf("\n");
}
void echo(char *a){
	printf("%s",a);
}

void main(){

	char icwd[1024]; 
		memset(icwd,'\0',sizeof(icwd));
	    getcwd(icwd, sizeof(icwd));

	char homeadd[100];
	memset(homeadd,'\0',sizeof(homeadd));
	char *homy;
	homy=getlogin();
	strcpy(homeadd,"/home/");
	strcpy(&homeadd[strlen("/home/")],homy);

	char *tepo="./ls";   
    char lscall[1024];
    memset(lscall,'\0',sizeof(lscall));
    strcpy(lscall,icwd);
    memset(&lscall[strlen(icwd)],'/',1);
    memcpy(&lscall[strlen(icwd)+1],tepo,strlen(tepo));

    char *tepo2="./date";
    char datecall[1024];
    memset(datecall,'\0',sizeof(datecall));
    strcpy(datecall,icwd);
    memset(&datecall[strlen(icwd)],'/',1);
    memcpy(&datecall[strlen(icwd)+1],tepo2,strlen(tepo2));

    char *tepo3="./mkdir";
    char mkdircall[1024];
    memset(mkdircall,'\0',sizeof(mkdircall));
    strcpy(mkdircall,icwd);
    memset(&mkdircall[strlen(icwd)],'/',1);
    memcpy(&mkdircall[strlen(icwd)+1],tepo3,strlen(tepo3));

    char *tepo4="./rm";
    char rmcall[1024];
    memset(rmcall,'\0',sizeof(rmcall));
    strcpy(rmcall,icwd);
    memset(&rmcall[strlen(icwd)],'/',1);
    memcpy(&rmcall[strlen(icwd)+1],tepo4,strlen(tepo4));

    char *tepo5="./cat";
    char catcall[1024];
    memset(catcall,'\0',sizeof(catcall));
    strcpy(catcall,icwd);
    memset(&catcall[strlen(icwd)],'/',1);
    memcpy(&catcall[strlen(icwd)+1],tepo5,strlen(tepo5));

    char *tepo6="./catE";
    char catEcall[1024];
    memset(catEcall,'\0',sizeof(catEcall));
    strcpy(catEcall,icwd);
    memset(&catEcall[strlen(icwd)],'/',1);
    memcpy(&catEcall[strlen(icwd)+1],tepo6,strlen(tepo6));

    char *tepo7="./catn";
    char catncall[1024];
    memset(catncall,'\0',sizeof(catncall));
    strcpy(catncall,icwd);
    memset(&catncall[strlen(icwd)],'/',1);
    memcpy(&catncall[strlen(icwd)+1],tepo7,strlen(tepo7));

    char *tepo8="./dateu";
    char dateucall[1024];
    memset(dateucall,'\0',sizeof(dateucall));
    strcpy(dateucall,icwd);
    memset(&dateucall[strlen(icwd)],'/',1);
    memcpy(&dateucall[strlen(icwd)+1],tepo8,strlen(tepo8));

    char cd[1024];

	char input[100];
	char optional[100];
	char hist[1000][100];
	for(int i=0;i<1000;i++){
		memset(hist[i],'\0',100);
	}
	int count=0;


	while(1){
		memset(input,'\0',sizeof(input));
		memset(optional,'\0',sizeof(optional));
		scanf("%s",input);

		memcpy(hist[count],input,strlen(input));

		if(strcmp(input,"cd")==0){
			scanf("%s",optional);
			memcpy(&hist[count][2]," ",1);
			memcpy(&hist[count][3],optional,strlen(optional));
			errno=0;
			if(strcmp(optional,"~")==0){
				chdir(homeadd);
			}
			else if(strcmp(optional,"-L")==0||strcmp(optional,"-P")==0){
				if(strcmp(optional,"-P")==0){printf("not following symbolic links\n");}
				char optional1[100];
				memset(optional1,'\0',100);
				scanf("%[^\n]%*c",optional1);
				memcpy(&hist[count][3+strlen(optional)],optional1,strlen(optional1));
				if(optional1[0]=='\0'){
					chdir(homeadd);
				}
				else{
					chdir(&optional1[1]);
				}
			}
			else{
				chdir(optional);
			}
			if(errno!=0){
			printf("%s\n", strerror(errno));
			}
			curdir();
		}
		else if(strcmp(input,"echo")==0){
			// scanf("%s",optional);
			fgets(optional, 100, stdin);//note fgets also takes the \n character at the end.
			
			memcpy(&hist[count][4],optional,strlen(optional)-1);
			// chdir(optional);
			if(optional[1]=='-' && optional[2]=='n'){
				int endc=4;
				while(optional[endc]!='\n'){
					endc++;
				}
				char toprint[100];
				memcpy(toprint,&optional[4],endc-4);
				echo(toprint);
			}
			else if(optional[1]=='-' && optional[2]=='E'){
				echo(&optional[4]);
			}
			else{
				echo(&optional[1]);
			}
		}
		else if(strcmp(input,"pwd")==0){
			char nouse2[3];
			scanf("%[^\n]%*c",nouse2);
			curdir();
		}
		else if(strcmp(input,"history")==0){
			char faltu[10];
			memset(faltu,'\0',3);
			scanf("%[^\n]%*c",faltu);
			if(strcmp(faltu," -c")==0){
				for(int i=0;i<1000;i++){
					memset(hist[i],'\0',100);
				}
				count=-1;
				printf("history cleared:\n");
			}
			else if(faltu[1]=='-'&&faltu[2]=='d'){
				strtok(faltu," ");
				int index=atoi(strtok(NULL," "));
				memset(hist[index],'\0',sizeof(hist[index]));
				strcpy(hist[index],"this was deleted");
				printf("history at index %d deleted\n",index);
			}
			else{
				for(int i=0;i<1000;i++){
					if(hist[i][0]!='\0'){
						printf("  %d  ",i);
					printf("%s\n",hist[i]);}
					else {break;}
				}
			}
		}

		else if(strcmp(input,"exit")==0){
			printf("You have Exited the Terminal\n");
			break;
		}

		else if(strcmp(input,"ls")==0){//external commands starts here
			char nouse[3];
			scanf("%[^\n]%*c",nouse);//implemented ls -a,ls -f
			memcpy(&hist[count][2],nouse,strlen(nouse));
			pid_t pid;
			pid=fork();
			if(pid<0){
				fprintf(stderr,"Fork Failed");
			}
			else if(pid==0){
				getcwd(cd,sizeof(cd));
				char *args[]={lscall,cd,NULL}; 
        		execvp(args[0],args);
			}
			else{
				waitpid(pid,0,2);
			}
		}
		else if(strcmp(input,"date")==0){
			char uflad[100];
			scanf("%[^\n]%*c",uflad);
			if(uflad[0]=='\0'){
				pid_t pid;
				pid=fork();
				if(pid<0){
					fprintf(stderr,"Fork Failed");
				}
				else if(pid==0){
					getcwd(cd,sizeof(cd));
					char *args[]={datecall,NULL}; 
	        		execvp(args[0],args);
				}
				else{
					waitpid(pid,0,2);
				}
			}
			// else if(uflad[1]=='-'&&uflad[2]=='u'){
			else{
				memcpy(&hist[count][4],uflad,strlen(uflad));
				pid_t pid;
				pid=fork();
				if(pid<0){
					fprintf(stderr,"Fork Failed");
				}
				else if(pid==0){
					getcwd(cd,sizeof(cd));
					char *args[]={dateucall,NULL}; 
	        		execvp(args[0],args);
				}
				else{
					waitpid(pid,0,2);
				}
			}
		}

		else if(strcmp(input,"mkdir")==0){
			scanf("%s",optional);
			memcpy(&hist[count][5]," ",1);
			memcpy(&hist[count][6],optional,strlen(optional));
			errno=0;
			if(strcmp(optional,"-v")==0||strcmp(optional,"-Z")==0){
				getchar();
				scanf("%s",optional);
				memcpy(&hist[count][8]," ",1);
				memcpy(&hist[count][9],optional,strlen(optional));
			}
			{
				pid_t pid;
				pid=fork();
				if(pid<0){
					fprintf(stderr,"Fork Failed");
				}
				else if(pid==0){
					getcwd(cd,sizeof(cd));
					char *args[]={mkdircall,cd,optional,NULL}; 
	        		execvp(args[0],args);
				}
				else{
					waitpid(pid,0,2);
				}
			}
		}

		else if(strcmp(input,"rm")==0){
			int simple=1;
			int kj=0;
			int tk=0;
			char prompt[1];
			memset(optional,'\0',sizeof(optional));
			scanf("%s",optional);
			memcpy(&hist[count][2]," ",1);
			memcpy(&hist[count][3],optional,strlen(optional));
			if(strcmp(optional,"-i")==0||strcmp(optional,"-f")==0){
				simple=0;
				if(strcmp(optional,"-i")==0){kj=1;}
				else if(strcmp(optional,"-f")==0){
					tk=1;
				}
				memset(optional,'\0',sizeof(optional));
				scanf("%s",optional);
				memcpy(&hist[count][5]," ",1);
				memcpy(&hist[count][6],optional,strlen(optional));
			}

			if(kj==1){
				printf("rm: remove regular file '%s'?(y/n)\n",optional);
				getchar();
				scanf("%c",&prompt[0]);
			}
			if(tk==1||prompt[0]=='y'||simple==1){
				pid_t pid;
				pid=fork();
				if(pid<0){
					fprintf(stderr,"Fork Failed");
				}
				else if(pid==0){
					getcwd(cd,sizeof(cd));
					char *args[]={rmcall,cd,optional,NULL}; 
	        		execvp(args[0],args);
				}
				else{
					waitpid(pid,0,2);
				}
			}
			else{
				printf("The file was not deleted\n");
			}
		}

		else if(strcmp(input,"cat")==0){
			scanf("%s",optional);
			memcpy(&hist[count][3]," ",1);
			memcpy(&hist[count][4],optional,strlen(optional));
			if(strcmp(optional,"-E")==0){
				scanf("%s",optional);
				memset(&hist[count][6],' ',1);
				memcpy(&hist[count][7],optional,strlen(optional));
				pid_t pid;
				pid=fork();
				if(pid<0){
					fprintf(stderr,"Fork Failed");
				}
				else if(pid==0){
					getcwd(cd,sizeof(cd));
					char *args[]={catEcall,cd,optional,NULL}; 
	        		execvp(args[0],args);
				}
				else{
					waitpid(pid,0,2);
				}
			}
			else if(strcmp(optional,"-n")==0){
				scanf("%s",optional);
				memset(&hist[count][6],' ',1);
				memcpy(&hist[count][7],optional,strlen(optional));
				pid_t pid;
				pid=fork();
				if(pid<0){
					fprintf(stderr,"Fork Failed");
				}
				else if(pid==0){
					getcwd(cd,sizeof(cd));
					char *args[]={catncall,cd,optional,NULL}; 
	        		execvp(args[0],args);
				}
				else{
					waitpid(pid,0,2);
				}
			}
			else{
				pid_t pid;
				pid=fork();
				if(pid<0){
					fprintf(stderr,"Fork Failed");
				}
				else if(pid==0){
					getcwd(cd,sizeof(cd));
					char *args[]={catcall,cd,optional,NULL}; 
	        		execvp(args[0],args);
				}
				else{
					waitpid(pid,0,2);
				}
			}
		}

		else {
			printf("This is not a VALID Command: Try again\n");
		}
		count++;
	}
	
}
