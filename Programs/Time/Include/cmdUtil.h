#ifndef __CDMUTIL_H
#define __CDMUTIL_H

/*command structure*/
typedef struct command{
	char *cmd;    //command including full path
	char **cmdarg; //arguments to the command
	char **cmd_env; //command environment (to be updated)
	int ncomArgs; //no of arguments for the command
}CMD;

#endif