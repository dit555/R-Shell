#!/bin/sh

./../rshell "(" echo hello ")" "&&" "(" echo is ")" "&&" "(" echo '"it me"' "&&" echo '"youre"' ")" "&&" "(" ls -j ")" "||" "(" ls -j ")" "||" "(" echo '"looking for"' ")" ";" echo success
