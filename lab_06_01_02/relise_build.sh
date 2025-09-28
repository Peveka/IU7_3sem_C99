#!/bin/bash

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")

# Проверка существования файла исходного кода
for file in "$dir"/*.c; do
    if [ ! -f "$file" ]; then
        echo "No file *.c in script directory!"
        exit 2
    fi
    break
done

for c_file in "$dir"/*.c; do
    # Компиляция программы с ключами для релизной сборки
    if ! gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -O2 -c -o "${c_file/%.c/.o}" "$c_file"
    then
        exit 1
    fi
done

# Компоновка исполняемого файла в случае успешной компиляции
gcc -o "$dir"/app.exe "$dir"/*.o -lm