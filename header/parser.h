#ifndef PARSER
#define PARSE

#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using std::string;

class Parser{
public:
	Parser(){};
	void prompt(int argc, char** argv);
	void parse(string input);
	bool execute(int argc, char** argv, bool paren);
	int list(int argc, char** argv, pid_t cpid, int status);



};

#endif
