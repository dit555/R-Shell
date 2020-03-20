#ifndef HELP
#define HELP

#include "cmd.h"

class Help :public Command{
public:
	Help(){};
	void execute(int argc, char** argv, bool test);
};




#endif
