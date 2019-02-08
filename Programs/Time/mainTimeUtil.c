#include"timeUtil.h"
#include"jobUtil.h"
#include<string.h>


#define COMMANDLEN 2048

/*stripArgs
description:
Param1: char *str i.e string porinter holding the command + argument
Param2: char ***retarg i.e return argument holding the tokenized argument list
return: int i.e no of tokens created. 
*/
int stripArgs(char *str,char ***retarg){

	char *ptr,temp[COMMANDLEN],*tok;
	int index=0,notok=1;	

	strcpy(temp,str);
	*retarg=NULL;
	ptr = temp;
	tok = strtok(ptr," ");
	while((tok = strtok(NULL," ")))
		notok++;

	strcpy(temp,str);
	ptr = temp;
	*retarg = malloc(notok * sizeof(char *)); //allocate space to store the data
	tok = strtok(ptr," ");
	for(index=0;index<notok;index++){
		(*retarg)[index] = malloc(strlen(tok)+1);
		strcpy((*retarg)[index],tok);
		tok = strtok(NULL," ");
	}

	return notok;
}


int main(int argc, char *argv[])
{
	/*call the time related routines here*/
	time_t curtime,endtime;
	char *cmd;
	char **cmd_arg;
	char **envptr= { NULL };
	int nocom,ex_ret=0,status;
	
	//second aregument is the full path to the binary 
	if(argc==3){
		if(argv[2][0]==' ')
			exit(EXIT_FAILURE);

		nocom=stripArgs(argv[2],&cmd_arg);
		cmd_arg[nocom]=NULL;
		
		cmd = argv[1];

		/*Record the pid of the process*/
		pid_t pid; 

		recordTime(&curtime);
		printf("ST : %ld\n",curtime);
		/*fork and exec your code here*/

		/*continue to write your own fork and exec util here*/
		pid = fork();

		/*Error check to be safe the fork didn't fail*/
		if(pid == -1){
			printf("Error : FORK FAILED\n");
			exit(EXIT_FAILURE);
		}
		/*Your code for child goes here 
		program to execute to check the time consumed*/
		else if(pid == 0){
				ex_ret = execve(cmd,cmd_arg,envptr);
				if(ex_ret == -1){
					printf("Error on execution on the binary %s with error no : %d ",cmd,errno);
				}
		}
		else{
			/*record a job here */
			jobCreate(pid,JB_FRK);			
			/*check in the parent on how the sub process executed*/
			if(waitpid(pid,&status,0) > 0){
				if(WIFEXITED(status) && !WEXITSTATUS(status))
					printf("Program executed successfully");
				else if(WIFEXITED(status) && WEXITSTATUS(status)){
					if(WEXITSTATUS(status) == 127)
						printf("execve failed");
					else
						printf("Progrm terminated abnormally with retval %d",WEXITSTATUS(status));
				}
				else{
					printf("Abnormal Program termination %d",errno);
				}
			}
			else{
				printf("Wait on child %d FAILED\n",pid);
			}
		}	
		jobList();
		/*collect the exit status if it completed successfully
		collect the end time and provide the time difference*/
		recordTime(&endtime);
		printf("\nET : %ld\n",endtime);

	}
	else{
		printf("Insufficient Parameter Error\n");
	}

	return 0;
}