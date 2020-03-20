#include<iostream>
#include <string.h>

#include"../header/help.h"

using std::cout;
using std::endl;


void Help::execute(int argc, char** argv, bool test){
	char expect[] = "help";
	
	if(strcmp(argv[0], expect) == 0 && !test){
		cout << "commands avalable" << endl;
		cout << endl << "- info " << " " << " prints out student info"<< endl;
		cout << "- test <flag> <path>   True or False depending on path existing" << endl;
		cout << "	" << "flags avalible: " << endl;
		cout << "		" << "-e   checks if file or directory exists" << endl;
		cout << "               " << "-f   checks if file exists" << endl;
		cout << "               " << "-d   checks if directory exists" << endl;
		cout << "               " << "<no flag>   defaults to -e" << endl;
		cout << "- [ <flag> <path> ]   alternate form of -test" << endl;
		cout << "- e   to exit" << endl;
		cout << "- any command that works in BASH works as well" << endl;
	
		exit(0);
	}
	else if(strcmp(argv[0], expect) == 0 && test){
                //effectively the same except, instead of testing for a large input
                //we can just test for a small one
                cout << "poop";
        }
	else
		exit(1);
}
