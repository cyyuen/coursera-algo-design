#!/bin/bash

TEST1="10.txt"
TEST2="100.txt"
TEST3="1000.txt"

ignore=`make`

function assert {

	if [ $2 == $3 ]; then
		printf '\e[32m %s Succeed! \e[0m\n' $1 
	else
		printf '\e[31m %s Failed! \e[0m\n' $1
	fi
}


echo "Testing"

echo "./ex1"

assert $TEST1 `./ex1 < $TEST1` 25
assert $TEST2 `./ex1 < $TEST2` 615
assert $TEST3 `./ex1 < $TEST3` 10297

echo "./ex2"

assert $TEST1 `./ex2 < $TEST1` 29
assert $TEST2 `./ex2 < $TEST2` 587
assert $TEST3 `./ex2 < $TEST3` 10184

echo "./ex3"

assert $TEST1 `./ex3 < $TEST1` 21
assert $TEST2 `./ex3 < $TEST2` 518
assert $TEST3 `./ex3 < $TEST3` 8921
