#!/bin/bash

dir=$(dirname "$(readlink -f "$0")")/../..
if [ ! -f "$dir"/app.exe ]; then
    echo "No app.exe in project directory!"
    exit 3
fi

if [ "$1" = "-v" ]; then
    verbose=1
fi

tests_count=0
tests_failed=0

for file_in in "$dir"/func_tests/data/pos_*_in.txt; do

    file_out=${file_in/%in.txt/out.txt}
    file_args=${file_in/%in.txt/args.txt}
    test_name="$(basename "$file_in")"

    if [ ! -f "$file_out" ]; then
        echo "No pos out file for $test_name!"
        continue
    fi

    if [ ! -f "$file_args" ]; then
        echo "No pos args file for $test_name!"
        continue
    fi

    test_name=${test_name#pos_}
    test_name=${test_name%_in.txt}

    tests_count=$((tests_count + 1))

    if "$dir"/func_tests/scripts/pos_case.sh "$file_in" "$file_out" "$file_args"
    then
        if [ "$verbose" ]; then
            echo "Pos test $test_name OK"
        fi
    else
        tests_failed=$((tests_failed + 1))
        if [ "$verbose" ]; then
            echo "Pos test $test_name FAIL!"
        fi
    fi
done

for file_in in "$dir"/func_tests/data/neg_*_in.txt; do
    if [ ! -f "$file_in" ]; then
        if [ "$verbose" ]; then
            echo "No neg_*_in files in dir!"
        fi
        break
    fi

    file_args=${file_in/%in.txt/args.txt}
    test_name="$(basename "$file_in")"

    if [ ! -f "$file_args" ]; then
        echo "No negative args file for $test_name!"
        continue
    fi

    test_name=${test_name#neg_}
    test_name=${test_name%_in.txt}

    tests_count=$((tests_count + 1))

    if "$dir"/func_tests/scripts/neg_case.sh "$file_in" "$file_args"
    then
        if [ "$verbose" ]; then
            echo "Neg test $test_name OK"
        fi
    else
        tests_failed=$((tests_failed + 1))
        if [ "$verbose" ]; then
            echo "Neg test $test_name FAIL!"
        fi
    fi
done

echo "$tests_failed out of $tests_count tests failed"

exit $tests_failed