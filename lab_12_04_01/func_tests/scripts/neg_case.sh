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

if ./app.exe "${args[@]}" > /dev/null 2>&1; then
    exit 1
fi

# Выходной файл не должен создаваться при ошибке
output_file="${args[1]}"
if [ -f "$output_file" ]; then
    rm -f "$output_file"
    exit 1
fi

exit 0
