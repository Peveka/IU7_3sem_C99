#!/bin/bash

dir=$(dirname "$(readlink -f "$0")")

for c_file in "$dir"/*.c; do
    # Компиляция программы для тестирования покрытия кода (coverage/gcov)
    if ! gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g --coverage -c -o "${c_file/%.c/.o}" "$c_file"
    then
        exit 1
    fi
done

#Компоновка исполняемого файла из объектных модулей после успешной компиляции
gcc --coverage -o "$dir"/app.exe "$dir"/*.o -lm