#!/bin/bash

dir=$(dirname "$(readlink -f "$0")")

for c_file in "$dir"/*.c; do
    # Компиляция программы с undefined behavior санитайзером
    if ! clang -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -fsanitize=undefined -fno-omit-frame-pointer -O0 -g -c -o "${c_file/%.c/.o}" "$c_file"
    then
        exit 1
    fi
done

clang -fsanitize=undefined -o "$dir"/app.exe "$dir"/*.o -lm