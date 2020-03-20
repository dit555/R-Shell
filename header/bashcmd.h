#ifndef BASHCMD
#define BASHCMD

#include "cmd.h"

class Bashcmd : public Command{
public:
	Bashcmd(){};
	void execute(int argc, char** argv, bool test);

};


#endif
