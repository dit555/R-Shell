## CS 100 Programming Project
   
### Project Information
Winter quater 2020:  
Dumitru Chiriac, 862126186, dchir002@ucr.edu   

### Introduction
We will be developing a shell by the name of R'Shell. Its purpose will be to :  
* Print a command prompt (R'Shell $)
* Read a line of commands and connectors
* Parse the input
* Execute accordingly

### Diagram
![OMT Diagram](https://github.com/cs100/assignment-fartinwind/blob/master/images/OMT%20Diagram.png?raw=true)
### Classes
int argc stores the number of inputs.  
char** argv stores the inputs.  
bool test is to determine if the classes are being tested upon. If there is testing classes will not run the exit command which will allow gtest to work. In additon, classes the print out their output will instead print out a more convinent message for testing.

      Parser:
         void prompt(int argc, char** argv); - prompts the user for input as a string, or recieves input from command line input
         void parse(string input); - recieves string from prompt, breaks down the string into commands in char** format and in 
         accordance to whitespace '_', quotations "", and comments #. 
         bool execute(int argc, char** argv, bool paren); - creates forks as needed to deal with connectors, runs the commands in   
         parenthesis recursively, and returns true or false after it is done running (the true/false it used to determine if the 
         commands in parenthesis were executed successfully). In addition, runs redirection as appropriate e.g <, > , >>, and |. Pipe  
         does not work
         int list(int argc, char** argv, pid_t cpid, int status); - contains if statements that execute the commands
      
      Cmd: (Parent Class)
         virtual void execute(int argc, char** argv, bool test) = 0; - virtual function to be overridden by child classes
     
      Info: (Child of Cmd)
         void execute(int argc, char** argv, bool test); - prints out student info (like in names.txt), calls exit(0) on success and 
         exit(1) otherwise.
         
      Help: (Child of Cmd)
         void execute(int argc, char** argv, bool test); - prints out the possible commands, calls exit(0) on success and 
         exit(1) otherwise.
      
      TestCmd: (Child of Cmd)
         void execute(int argc, char** argv, bool test); - Tests is a path exitst. Reads both `test` and `[]` as valid command name, 
         prints out `(True)` if a path exists and `(False)` otherwise. If `(True)` then it `exit(0)`s otherwise `exit(1)`. It can change 
         mode according to the flags `-e` `-f` and `-d`, defaults to `-e` if not flag is inputed. 
         
      Bashcmd: (Child of Cmd)
         void execute(int argc, char** argv, bool test); - uses execvp() to run any bash command, execvp() calls exit(0) on success and exit( > 1) on failure;
         

### Unit Tests
There are four unit tests, all using google test.  
There cannot be a test for `Bashcmd` because execvp() calls exit() automatically which stops gtest.  
  
**InfoTest**: Declares an `Info` class and calls `execute(int argc, char** argv, bool test);` where `argc` will be 1 because the only input is `char *argv[0] = "info"` and `bool test = true`. When `bool test` is true then `execute();` will call an alternate funtion that prints out a word (instead of the two sentences it would have been) and does not call `exit();`.  
  
**HelpTest**: Declares a `Help` class and calls `execute(int argc, char** argv, bool test);` where `argc` will be 1 because the only input is `char *argv[0] = "help"` and `bool test = true`.  
  
**TestCmdTest**: runs two tests, one for `test` command and one for the `[]` version of test. Both exhaustively test each case of both a file and directory with each possible flag, with 16 cases in total.

### Integration Tests:
These tests test R'Shell as a whole, by calling `./../rshell` and the commands to be tested after. For Example: `./../rshell info "&&" echo test`. Since the test extecutables `.sh` are in a subdirectory of the one where the executable for R'Shell is, we have to call `../` to go to that directory and `./` to execute it. In additon, connectors must be put in quotations or else Bash will run then seperately. To test `Bashcmd` we use the `echo` command becuase it is the easiest to test.  
To prompt a fail condition we use `ls -j`, where it will be run by Bash and Bash will return fail. We use this to test the `||` connector.  
  
**single_commands_test**: Runs a test for info, help, and echo.  
  
**commented_commands_test.shs**: `echo`s `success` and is followed by a `#` and other commands. if the test is succesfull, none of the commands following `#` will execute.  
  
**connected_commands_test.shs**: runs 8 inputs connected by connectors `&&`, `||`, and `;` echoing out success if successful.  
  
**test_literal_tests.sh**: runs 8 cases with test command, each case uses connectors to echo `success` if the test has done what was needed. If the test command was expected to fail, `||` was used to run the next command.  
  
**test_symbolic_test.sh**: same as `test_literal_tests.sh` escept uses the `[]` version of the test command.  
  
**precedence_tests.sh**: has a chain of seven commands in parenthesis in including connecters within some. It will print out: "hello is it me you are (bash error message ) (bash error message) looking for" then prints out `success`.

**input_redirection_tests.sh**: tests `<`  
  
**output_redirection_tests.sh**: tests `>` and `>>`  
  
**pipe_operator_tests.sh**: tests `pipe`
