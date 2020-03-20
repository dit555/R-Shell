#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#include "info.cpp"
#include "help.cpp"
#include "bashcmd.cpp"
#include "testcmd.cpp"
#include "../header/parser.h"


using std::cout;
using std::getline;
using std::cin;
using std::string;
using std::endl;





void Parser::prompt(int argc, char** argv){
	string input;

	//begin R'Shell
	cout << "--------------------------------------------------------" << endl;
        cout << "Welcome to R'Shell, enter 'help' for a list of commands," << endl;
        cout << "'e' to exit, or 'info' for student information" << endl << endl;
	
	if (argc > 1) {
		cout << "R'shell $ ";
		for (int i = 1; i < argc; i++){
			if (i == 1){
				input = argv[1];
			}
			else{
				input.append(" ");
				input.append(argv[i]);
			}
		} 
		cout << input <<  endl;
		parse(input);
	}
	else{
        while(true){
		//prompt uset
		cout << "R'Shell $ ";
                getline(cin, input);

		//exit
		if(input == "e")
                        break;

                parse(input);

        }
	}
}

void Parser::parse(string input){

	string inputs[40];

	//separate each input
	input.append(" ");

        int inputIndex = 0;
        int i1 = 0;
        int i2 = 0;
        for (int i = 0; i < input.size(); i++){
		//check for comment
		if (input[i] == '#'){
                        i2 = i - i1;
                        inputs[inputIndex] = input.substr(i1, i2);
                        inputIndex++;
                        break;
                }
		//check for space
		if (input[i] == ' ') {
                        i2 = i - i1;
                        inputs[inputIndex] = input.substr(i1, i2);
                        inputIndex++;
                        i1 = i + 1;
                }
		//check for quotations
		 if (input[i] == '\"'){
                        int i1t = i + 1;
                        int i2t;
                        for (int j = i + 1; j < input.size(); j++){
                                if (input[j] == '\"'){
                                        i2t = j - i1t;
                                        inputs[inputIndex] = input.substr(i1t, i2t);
                                        inputIndex++;
                                        i1 = j + 2;
                                        i = j + 1;
                                        break;
                                }

                        }


                }
		
        }

		//put the separated inputs in argv
		char** argv = new char*[inputIndex];
        for (int i = 0; i < inputIndex; i++) {
                char* temp = new char[inputs[i].size() + 1];
                for (int j = 0; j < inputs[i].size(); j++)
                        temp[j] = inputs[i][j];
                argv[i] = temp;
        }

	
        int argc = inputIndex;

        execute(argc, argv, false);
        delete[] argv;


}

bool Parser::execute(int argc, char** argv, bool paren){

        bool connector = false;
	bool doNothing = false;
	
	//check for redirects
	int redirNum = 0;
	bool redir = false;
	for (int i = 0; i < argc; i++){
		if (strcmp(argv[i], "<") == 0 || strcmp(argv[i], ">") == 0 || strcmp(argv[i], ">>") == 0 || strcmp(argv[i], "|") == 0){
			redirNum++;
			redir = true;	
		}
	}

	//handle redirects
	if (redir){
		int lastFound = 0;
		int lastPipeFd;

		bool pipeb = false;
		for (int i = 0; i < argc; i++){
			 
			if (strcmp(argv[i], "<") == 0){
				int fd, pid, status;
				pid = fork();

				if (pid == 0){
					fd = open(argv[i + 1], O_RDONLY, 0);
					dup2(fd, STDIN_FILENO);
			
                        	        char** left = new char*[i - lastFound];
					int fart = 0;
					for (int j = lastFound; j < i; j++){
						left[fart] = argv[j];
						fart++;
					}
						
                       		        list(i - lastFound, left, pid, status);
                        		
					lastFound = i + 1;
					close(fd);
					delete[] left;
					exit(0);
					
				}
				waitpid(pid, &status, 0);
			}
			
			if (strcmp(argv[i], ">") == 0){
				int fd, pid, status;
                                pid = fork();

                                if (pid == 0 && !pipeb){
                                        fd = open(argv[i + 1], O_WRONLY | O_TRUNC, 0);
                                        dup2(fd, STDOUT_FILENO);

                                        char** left = new char*[i - lastFound];
                                        int fart = 0;
                                        for (int j = lastFound; j < i; j++){
                                                left[fart] = argv[j];
                                                fart++;
                                        }

                                        list(i - lastFound, left, pid, status);

                                        lastFound = i + 1;
                                        close(fd);
                                        delete[] left;
                                        exit(0);

                                }
				
				else if (pid == 0 && pipeb){
                                        fd = lastPipeFd;
                                        dup2(fd, STDOUT_FILENO);

                                        char** left = new char*[i - lastFound];
                                        int fart = 0;
                                        for (int j = lastFound; j < i; j++){
                                                left[fart] = argv[j];
                                                fart++;
                                        }

                                        list(i - lastFound, left, pid, status);

                                        lastFound = i + 1;
                                        close(fd);
                                        delete[] left;
                                        exit(0);

                                }

                                waitpid(pid, &status, 0);
				
				
			}
			
			if (strcmp(argv[i], ">>") == 0){
                                int fd, pid, status;
                                pid = fork();

                                if (pid == 0){
                                        fd = open(argv[i + 1], O_WRONLY | O_APPEND, 0);
                                        dup2(fd, STDOUT_FILENO);
					
                                        char** left = new char*[i - lastFound];
                                        int fart = 0;
                                        for (int j = lastFound; j < i; j++){
                                                left[fart] = argv[j];
                                                fart++;
                                        }

                                        list(i - lastFound, left, pid, status);

                                        lastFound = i + 1;
                                        close(fd);
                                        delete[] left;
                                        exit(0);

                                }
                                waitpid(pid, &status, 0);


                        }

			if (strcmp(argv[i], "|") == 0){
				
				int lastFoundPipe = i;
				int p[2];
				int fd;
				FILE * fp;
				pipe(p);
				
				int pid, status, c;
				
				pid = fork();
				if (pid == 0){
					for (int j = i; j < argc; j++){
						
						if (i == j){
							fp = fopen(argv[i - 1], "r+");
                                        		while((c = getc(fp)) != EOF)
            							write(p[1], &c, 1);	
							fd = p[1];
							dup2(fd, STDIN_FILENO);
							fclose(fp);
						}
						
						if (strcmp(argv[j], "|") == 0){
							int dist = 0; //distance to next |
							int pid2, status2;
							for (int k = j; k < argc; k++){
								if (strcmp(argv[k], "|") == 0)
									dist++; 
							}
							char** right = new char*[dist];
							for (int m = 0; m < dist; m++)
								right[m] = argv[j + 1 + m];
							if (pid2 == fork())
								list(dist, right, pid2, status2);
							else
								waitpid(pid2, &status2, 0);
							delete[] right;	 	
						}
						else if (strcmp(argv[j], ">") == 0){
							fd = p[0];
							lastPipeFd = fd;
							pipeb = true;
                                               		close(fd);
							close(p[0]);
							close(p[1]);
							exit(fd);
							break;
                                        	}

					}
				waitpid(pid, &status, 0);
				lastPipeFd = WEXITSTATUS(status);
				cout << lastPipeFd << endl;
				}			
			}
		}	
	}

	


	
	//check for conectorss && || ; and run respectively
	int lastFound = 0;
	int i;
	for (i = 0; i < argc; i++ ){
		//cout << " - " << i << endl;
		bool parenSucAnd = true;
		bool parenSucOr = false;
		bool parenE = false;
		if (strcmp(argv[i], "(") == 0){
			//cout << "p found" << endl;
			bool endParen = false;
			
			int j;
			//check for end paren
			for (j = i + 1; j < argc; j++){
				int lenght = j - i - 1;
				char** tempArg = new char*[lenght];
				if (strcmp(argv[j], ")") == 0){
					endParen = true;
					parenE = true;
				}
				if (endParen){
					for (int k = 0; k < lenght; k++){
						tempArg[k] = argv[i + 1 + k];
					}
					parenSucAnd = execute(lenght, tempArg, true);
					parenSucOr = parenSucAnd;
					//cout << "-" << j << endl;
				}
				delete[] tempArg;
				if (endParen) break;
			}
			//have i start after closing parthesis
			if (endParen){
				i = j + 1;
				//cout << i << endl;
			}
			//to preven seg faults when the end parentesis is the last input
			if (i >= argc){
				//cout << "break" << endl;
				break; 
			}
		}
		if (strcmp(argv[i], "&&") == 0){
			if (!parenSucAnd)
				break;
			else if (!parenE){
				char** temp = new char*[i - lastFound];
				int k = 0;
				for (int j = lastFound; j < i; j++){
					temp[k] = argv[j];
					k++;
				}
				int arg = k;
				int stat;
				pid_t w;
				pid_t a = fork();
				if (a == 0)
					list(arg, temp, a, stat);
				w = waitpid(a, &stat, 0);
        			if ( w == -1){ cout << "wait failure" << endl;}
        			if ( WIFEXITED(stat)) {
                			const int ed = WEXITSTATUS(stat);
					lastFound = i + 1;
               		         	connector = true;
               		         	delete[] temp;
					doNothing = true;
					if (ed != 0) { 
						if (paren){
               	                         	
						        return false;
						}
						break;
					}
      		  		}
				doNothing = false;
			}	
		}
		// checks for ||
		if (strcmp(argv[i], "||") == 0){
			if (parenSucOr)
				break;
			else if (!parenE){
	                        char** temp = new char*[i - lastFound];
        	                int k = 0;
                	        for (int j = lastFound; j < i; j++){
                  	      	        temp[k] = argv[j];
                        	        k++;
                      	  	}
                      		int arg = k;
       	                	int stat;
                        	pid_t w;
                        	pid_t a = fork();
                        	if (a == 0)
                                	list(arg, temp, a, stat);
                       	 	w = waitpid(a, &stat, 0);
                        	if ( w == -1){ cout << "wait failure" << endl;}
                        	if ( WIFEXITED(stat)) {
                                	const int ed = WEXITSTATUS(stat);
                                	lastFound = i + 1;
                                	connector = true;
                                	delete[] temp;
                                	doNothing = true;
                                	if (ed == 0) { 
						break;
					}
                        	}
                        	doNothing = false;
			}
                }
		// check for ;
		if (strcmp(argv[i], ";") == 0){
                        char** temp = new char*[i - lastFound];
                        int k = 0;
                        for (int j = lastFound; j < i; j++){
                                temp[k] = argv[j];
                                k++;
                        }
                        int arg = k;
                        int stat;
                        pid_t w;
                        pid_t a = fork();
                        if (a == 0)
                                list(arg, temp, a, stat);
                        w = waitpid(a, &stat, 0);
                        if ( w == -1){ cout << "wait failure" << endl;}
                        if ( WIFEXITED(stat)) {
                                const int ed = WEXITSTATUS(stat);
                                lastFound = i + 1;
                                connector = true;
                                delete[] temp;
                                
                        }
                }
		//cout << i << argv[i] << endl;

	}
	if (connector && !doNothing){
		int poop = 0;
		pid_t w;
		char** lastArg = new char*[i - lastFound];
		for (int j = lastFound; j < argc; j++){
			lastArg[poop] = argv[j];
			poop++;
		}
		pid_t cpid;
	        int status;
        	cpid = fork();
        	if (cpid == 0)
			list(poop, lastArg, cpid, status);
		w = waitpid (cpid, &status, 0);
		if ( w == -1){ cout << "wait failure" << endl;}
		if ( WIFEXITED(status)) {
                	const int ed = WEXITSTATUS(status);

			if (ed == 0 )
				return true;
			else
				return false;
		}	
	}

	//if there are no connectors
	else if (!doNothing && !redir){
		pid_t cpid;
		pid_t w;
		int status;	
		cpid = fork();
		if (cpid == 0 )
			list(argc, argv, cpid, status);
		w = waitpid(cpid, &status, 0);
		if ( w == -1){ cout << "wait failure" << endl;}
		if ( WIFEXITED(status)) {
                        const int ed = WEXITSTATUS(status);
			
                        if (ed == 0 )
                                return true;
                        else
                                return false;
                }
	}
	return true;
}

int Parser::list(int argc, char** argv, pid_t cpid, int status){
	pid_t w;
	if (cpid == 0){
                if (strcmp (argv[0], "info") == 0){
                        Info a;
                        a.execute(argc, argv, false);
                }
                else if (strcmp (argv[0], "help") == 0){
                        Help a;
                        a.execute(argc, argv, false);
                }
		else if (strcmp (argv[0], "test") == 0){
			TestCmd a;
			a.execute(argc, argv, false);
		}
		else if (strcmp (argv[0], "[") == 0){
			TestCmd a;
			a.execute(argc, argv, false);
		
		}
                else{
                       	Bashcmd a;
                       	a.execute(argc, argv, false);
		}
        }
        w = waitpid(cpid, &status, 0);
        if ( w == -1){ cout << "wait failure" << endl;}
	if ( WIFEXITED(status)) {
                const int ed = WEXITSTATUS(status);
		return ed;
	}
	return 1;
}
