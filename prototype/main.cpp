#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/types.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;

void parse();
void runCmd(string cmd);

void runCmd(string cmd){
	cout << cmd << endl;
}

void parse(){
	while(true){
		//pid_t pid;
		//int status;
		
		string input;		
		cout << "$  ";
		cin >> input;
		
		cout << input << "\n";
		//check for exit command
		if (input == "exit")
			break;
		
		//creates a fort but results in fork bomb, to be fixed later
		/*
		//create a fork and send command to runCmd to execute 
		else {
			//check if fork failed
			if ((pid = fork()) < 0) {
				
				cout << "ERROR: forking child failed\n";
				exit(1);
			}
			//if valid do the thing			
			else if (pid == 0){
				runCmd(input);
			}
			//wait for completion of fork
			else {
				char a;
				
				while (a != 'a'){
					cin >> a;
				}
			}
			
		} */
	}	

}



int main() {
	
	parse();
	return 0;
}
