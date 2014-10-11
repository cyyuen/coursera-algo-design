#!/bin/bash

TEST1="test1"
TEST2="test2"
TEST3="test3"
TEST4="test4"

ignore=`make`

function assert {

	if [ $2 == $3 ]; then
		printf '\e[32m %s Passed! \e[0m\n' $1 
	else
		printf '\e[31m %s Failed! \e[0m\n' $1
	fi
}


echo "Testing"

echo "./knapsack"

assert $TEST1 `./knapsack < $TEST1` 1015873
assert $TEST2 `./knapsack < $TEST2` 1225054
assert $TEST3 `./knapsack < $TEST3` 1680893
assert $TEST4 `./knapsack < $TEST4` 2595819
