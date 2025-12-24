#!/bin/bash

dir=$(dirname "$(readlink -f "$0")")

for c_file in "$dir"/src/*.c; do
if ! gcc -std=c99 -Wall -Iinc -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g -c -o ${c_file/%.c/.o} "$c_file"
    then
        exit 1
    fi
done

gcc -o "$dir"/app.exe "$dir"/src/*.o -lm