#ifndef __PROCUTIL_H
#define __PROCUTIL_H

typedef struct process{
	int pid;
	int pipe_fd[2];
	
}PROC;

#endif