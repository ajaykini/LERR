#ifndef __JOBUTIL_H
#define __JOBUTIL_H
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

//types of JOBS
#define JB_FRK 2 // forked jobs
#define JB_INTERNAL 4 //internal Job

//Current State of the Jobs
#define JB_ST_WORKING 3 // working jobs hold this state
#define JB_ST_FAILED 6 // working jobs moved to failed or 
#define JB_ST_COMPLETED 12 // working jobs moved to finish state 
#define JB_ST_KILLED 24 // working job killed due to interruption 

#define JB_MASK 0xFFFF //job mask

#define JB_MAX 10

typedef struct TJob{
	pid_t jobID; //pid of the forked process
	int flag; // additional data to go here (used for hash)
	int state; //current stater of the process as a job entry
	int type; // any one of the job type as defeined above
	int retval; // return value collected fromt he process forked
	struct TJob *child;
	struct TJob *next;
}JOB;

JOB **jobTable;
JOB *curjob;
/*Initialize the job module for the current program*/
JOB **jobInit();
/*create a job and wait to check if it was successfully forked*/
JOB *jobCreate(pid_t jobID,int flags);
/*will add the created job into the jobtable*/
int jobAdd(JOB *job);
/*will mark the job as completed/failed/killed*/ 
int *jobDelete(JOB *job);
/*get information about the job history*/
int *jobHistory();
/*used to clear stale entries from the jobTable*/
int *jobClear();
/*list all the jobs int he jobTable*/
void jobList();

#endif