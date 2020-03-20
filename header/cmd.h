#ifndef command
#define command

class Command{
public:
	virtual void execute(int argc, char** argv, bool test) = 0;

};
#endif
