#!/bin/bash

dir=$(dirname "$(readlink -f "$0")")

for c_file in "$dir"/*.c; do
    # Компиляция программы с address санитайзером и отладочными данными
    if ! clang -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -fsanitize=address -fno-omit-frame-pointer -O0 -g -c -o "${c_file/%.c/.o}" "$c_file"
    then
        exit 1
    fi
done

# Компоновка исполняемого файла при компиляции
clang -fsanitize=address -o "$dir"/app.exe "$dir"/*.o -lm