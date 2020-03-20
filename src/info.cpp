#include<iostream>
#include <string.h>

#include"../header/info.h"

using std::cout;
using std::endl;


void Info::execute(int argc, char** argv, bool test){
	char expect[] = "info";
	
	if(strcmp(argv[0], expect) == 0 && !test){
		cout<<"Hongan Zhang " << "862156537 " << "hzhan265@ucr.edu"<< endl;
		cout << "Dumitru Chiriac " << "862126186 " << "dchir002@ucr.edu" << endl;
		exit(0);
	}
	else if(strcmp(argv[0], expect) == 0 && test){
		//effectively the same except, instead of testing for a large input
		// we can just test for a small one
		cout << "poop";
	}
	else{
		exit(1);
		
	}
}
