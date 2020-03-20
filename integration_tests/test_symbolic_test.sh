#!/bin/sh

./../rshell [ ../src/ ] "&&" echo success
./../rshell [ ../src/parser.cpp ]  "&&" echo success
./../rshell [ -e ../src/ ]  "&&" echo success
./../rshell [ -e ../src/parser.cpp ]  "&&" echo success
./../rshell [ -f ../src/ ]  "||" echo success
./../rshell [ -f ../src/parser.cpp ]  "&&" echo success
./../rshell [ -d ../src/ ] "&&" echo success
./../rshell [ -d ../src/parser.cpp ] "||" echo success

