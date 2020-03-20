#!/bin/sh

#there are more than three commands exiting in R'Shell
#due to the fact that there is a class that runs any
#valid command in bash. the echo command is the 
#easiest to test
./../rshell info
echo
echo
./../rshell help
echo
echo
./../rshell echo success
