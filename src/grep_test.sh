#!/bin/bash

TEST_FILE="../materials/jewsewer.txt"
MY_GREP="../build/bin/release/grep"
REAL_GREP="grep"

test_case(){
    local args=$1
    echo "testing $MY_GREP $args"
    $MY_GREP $args "the" $TEST_FILE >> my_out.txt
    $REAL_GREP $args "the" $TEST_FILE >> real_out.txt
    if diff -u my_out.txt real_out.txt; then
        echo "✅ PASSED $args"
    else 
        echo "❌ FAILED $args"
    fi 
    echo
}
test_case ""
test_case "-i"
test_case "-c"
test_case "-v"
test_case "-l"
test_case "-n"
test_case "-w"
test_case "-x"
test_case "-r"
test_case "-h"
test_case "-H"
test_case "-b"
test_case "-i -w"
test_case "-n -v"
test_case "-c -l"
test_case "-b -x"
test_case "-i -b"
test_case "-n -w"
test_case "-l -v"

echo "testing stdin"
echo "test input" | $MY_GREP | $REAL_GREP > my_out.txt
echo "test input" | $MY_GREP | $REAL_GREP > real_out.txt
diff -u my_out.txt real_out.txt && echo "✅ PASSED stdin" || echo "❌ FAILED stdin"
rm -rf my_out.txt real_out.txt