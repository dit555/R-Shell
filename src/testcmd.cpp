#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../header/testcmd.h"

using std::cout;
using std::endl;

void TestCmd::execute(int argc, char** argv, bool test){
	char expect1[] = "test";
	char expect2[] = "[";
	char expect3[] = "]";
	char flag1[] = "-e";
	char flag2[] = "-d";
	char flag3[] = "-f";

	int result;
	if (strcmp(argv[0], expect1) == 0 ){
		struct stat file;
		//default
		if ( argc == 2){
                        result = stat(argv[1], &file);
                        if (result == 0){
                                cout << "(True)";
				if (!test) {cout << endl;}
                                if (!test) {exit(0);}
                        }
                        else{
                                cout << "(False)";
				if (!test) {cout << endl;}
                                if (!test) exit(1);
                        }
                }

		
		//flag e
		else if( strcmp( argv[1], flag1) == 0 ){
			result = stat(argv[2], &file); 
			if (result == 0){
				cout << "(True)";
				if (!test) {cout << endl;}
				if (!test) exit(0);
			}
			else{
				cout << "(False)";
				if (!test) {cout << endl;}
				if (!test) exit(1);
			}
		}
		
		//flag d
		else if( strcmp( argv[1], flag2) == 0 ){
                        stat(argv[2], &file);
			result = S_ISDIR(file.st_mode);
                        if (result != 0){
                                cout << "(True)";
				if (!test) {cout << endl;}
                                if (!test) exit(0);
                        }
                        else{
                                cout << "(False)";
				if (!test) {cout << endl;}
                                if (!test) exit(1);
                        }
                }
	
		//flag f
		else if( strcmp( argv[1], flag3) == 0 ){
                        stat(argv[2], &file);
                        result = S_ISREG(file.st_mode);
                        if (result != 0){
                                cout << "(True)";
				if (!test) {cout << endl;}
                                if (!test) exit(0);
                        }
                        else{
                                cout << "(False)";
				if (!test) {cout << endl;}
                                if (!test) exit(1);
                        }
                }
		if (!test) {exit(1); cout << "oops" << endl;}
			
	}
	// {} variant
	else if (strcmp(argv[0], expect2) == 0 && strcmp(argv[argc - 1], expect3) == 0){
		struct stat file;
		//default
		if ( argc == 3){
                        result = stat(argv[1], &file);
                        if (result == 0){
                                cout << "(True)";
				if (!test) {cout << endl;}
                                if (!test) exit(0);
                        }
                        else{
                                cout << "(False)";
				if (!test) {cout << endl;}
                                if (!test) exit(1);
                        }
                }
		
		//flag e
		else if( strcmp( argv[1], flag1) == 0 ){
			result = stat(argv[2], &file); 
			if (result == 0){
				cout << "(True)";
				if (!test) {cout << endl;}
				if (!test) exit(0);
			}
			else{
				cout << "(False)";
				if (!test) {cout << endl;}
				if (!test) exit(1);
			}
		}

		//flag d
		else if( strcmp( argv[1], flag2) == 0 ){
                        stat(argv[2], &file);
			result = S_ISDIR(file.st_mode);
                        if (result != 0){
                                cout << "(True)";
				if (!test) {cout << endl;}
                                if (!test) exit(0);
                        }
                        else{
                                cout << "(False)";
				if (!test) {cout << endl;}
                                if (!test) exit(1);
                        }
                }

		//flag d
		else if( strcmp( argv[1], flag3) == 0 ){
                        stat(argv[2], &file);
                        result = S_ISREG(file.st_mode);
                        if (result != 0){
                                cout << "(True)";
				if (!test) {cout << endl;}
                                if (!test) exit(0);
                        }
                        else{
                                cout << "(False)";
				if (!test) {cout << endl;}
                                if (!test) exit(1);
                        }
                }
		if (!test) {exit(1); cout << "fart" <<endl;}		
	}
	else
		exit(1);

}

