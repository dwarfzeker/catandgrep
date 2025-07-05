#!/bin/bash

TEST_FILE="../materials/jewsewer.txt"
MY_CAT="../build/bin/release/cat"
REAL_CAT="cat"


test_case(){
    local args=$1
    echo "testing $MY_CAT $args"
    $MY_CAT $args $TEST_FILE >> my_out.txt
    $REAL_CAT $args $TEST_FILE >> real_out.txt

    if diff -u my_out.txt real_out.txt; then 
        echo "✅ PASSED $args"
    else 
        echo "❌ FAILED $args"
    fi 
    echo
}
test_case ""
test_case "-b"
test_case "-n"
test_case "-s"
test_case "-t"
test_case "-v"
test_case "-v -s"
test_case "-n -s"
test_case "-b -t"
test_case "-n -v"
test_case "-b -s"
test_case "-b -v"
test_case "-n -t"
test_case "-s -t"
test_case "-v -t"

echo "testing stdin"
echo "Test input" | $MY_CAT | $REAL_CAT > my_out.txt
echo "Test input" | $MY_CAT | $REAL_CAT > real_out.txt
diff -u my_out.txt real_out.txt && echo "✅ PASSED stdin" || echo "❌ FAILED stdin"

rm -rf my_out.txt real_out.txt
