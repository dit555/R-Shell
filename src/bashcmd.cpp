#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>

#include "../header/bashcmd.h"


void Bashcmd::execute(int argc, char** argv, bool test){
	
	char *cmd = argv[0];
	argv[argc] = NULL;
	execvp(cmd, argv);
	if(!test) {exit(0);}
	
	
}

