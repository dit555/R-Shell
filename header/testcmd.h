#ifndef TEST_CMD
#define TEST_CMD


#include "cmd.h"


class TestCmd : public Command {
public:
	TestCmd(){};
	void execute(int argc, char** argv, bool test);
};
#endif
