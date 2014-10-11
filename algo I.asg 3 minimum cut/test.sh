#!/bin/bash

TEST1="test1"
TEST2="test2"
TEST3="test3"

ignore=`make`

function assert {

	if [ $2 == $3 ]; then
		printf '\e[32m %s Passed! \e[0m\n' $1 
	else
		printf '\e[31m %s Failed! \e[0m\n' $1
	fi
}


echo "Testing"

echo "./mincut"

assert $TEST1 `./mincut < $TEST1` 2
assert $TEST2 `./mincut < $TEST2` 1
assert $TEST3 `./mincut < $TEST3` 3
