#!/bin/sh

#the connectors mush be in quotes otherwise bash will run them
#this also doubles as a test for R'Shell parsing quotations
./../rshell info "&&" ls -j "||" help "&&" ls -j ";" echo success
