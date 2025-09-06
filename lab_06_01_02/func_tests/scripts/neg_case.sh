#!/bin/bash

dir=$(dirname "$(readlink -f "$0")")/../..

cd "$dir" || exit 3

if [ ! -f ./app.exe ]; then
    echo "No file app.exe in project directory!"
    exit 2
fi

if [ $# -lt 2 ]; then
    echo "Error! Use: ./func_tests/scripts/neg_case.sh file_in file_args"
    exit 2
fi

if [ ! -f "$1" ] && [ ! -L "$1" ]; then
    echo "First param must be valid file!"
    exit 2
fi

if [ ! -f "$2" ] && [ ! -L "$2" ]; then
    echo "Second param must be valid file!"
    exit 2
fi

read -r -a args < "$2"

if ./app.exe "${args[@]}" > out.tmp 2>&1; then
    exit 1
fi
exit 0