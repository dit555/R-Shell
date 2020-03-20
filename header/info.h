#ifndef INFO
#define INFO

#include "cmd.h"

class Info :public Command{
public:
	Info(){};
	void execute(int argc, char** argv, bool test);
};




#endif
