#!/bin/bash

dir=$(dirname "$(readlink -f "$0")")

for c_file in "$dir"/*.c; do
    # Компиляция программы с memory санитайзером
    if ! clang -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -fsanitize=memory -fPIE -fno-omit-frame-pointer -O0 -g -c -o "${c_file/%.c/.o}" "$c_file"
    then
        exit 1
    fi
done

clang -fsanitize=memory -pie -o "$dir"/app.exe "$dir"/*.o -lm