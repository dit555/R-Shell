#!/bin/sh

./../rshell test ../src/ "&&" echo success
./../rshell test ../src/parser.cpp "&&" echo success
./../rshell test -e ../src/ "&&" echo success
./../rshell test -e ../src/parser.cpp "&&" echo success
./../rshell test -f ../src/ "||" echo success
./../rshell test -f ../src/parser.cpp "&&" echo success
./../rshell test -d ../src/ "&&" echo success
./../rshell test -d ../src/parser.cpp "||" echo success
