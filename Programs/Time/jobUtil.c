#include"jobUtil.h"

/*
DESC  : initialize the job module majorly the jobTable
PARAM :
*/
JOB **jonInit(){
	jobTable = (JOB **)malloc(sizeof(JOB *)*JB_MAX);

	return jobTable;
}
/*
DESC  : create a job and wait to check if it was successfully forked
PARAM :
	int jobID
	int flags
RET   :
*/
JOB *jobCreate(int jobID,int flags){
	//allocate memory for the current Job
	curjob = malloc(sizeof(JOB));

	/*Fill in the data for the created job structure*/
	curjob->jobID = jobID;
	curjob->state = flags;
	curjob->type = JB_ST_WORKING;

	/*set the curjob->child and the next beased on the previous job*/
	curjob->next = NULL;
	curjob->child = NULL;

	return curjob;
}

/*
DESC  : list all the jobs int he jobTable
PARAM : 
RET   :
*/
void jobList(){
	printf("PID:%d TYPE:%d RETVAL:%d STATE:%d",curjob->jobID,curjob->type,curjob->retval,curjob->state);
} 
