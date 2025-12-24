#!/bin/bash

# Получение абсолютного пути к исполняемому файлу
dir=$(dirname "$(readlink -f "$0")")/../..

cd "$dir" || exit 3

# Проверка на существование исполняемого файла
if [ ! -f ./app.exe ]; then
    echo "No app.exe in project directory!"
    exit 2
fi

# Проверка количества аргументов
if [ $# -lt 3 ]; then
    echo "Error! Use: ./func_tests/scripts/pos_case.sh file_in file_out file_args"
    exit 2
fi

# Проверка аргументов
if [ ! -f "$1" ] && [ ! -L "$1" ]; then
    echo "First param must be valid file!"
    exit 2
fi

if [ ! -f "$2" ] && [ ! -L "$2" ]; then
    echo "Second param must be valid file!"
    exit 2
fi

if [ ! -f "$3" ] && [ ! -L "$3" ]; then
    echo "Third param must be valid file!"
    exit 2
fi

#Считывание файлов args.txt в массив args
read -r -a args < "$3"

# Запуск программы с аргументами и сохранение вывода
if ! ./app.exe "${args[@]}" > ./out.tmp; then
    exit 1
fi

# Проверка comparator.sh полученного и эталонного вывода
if ! ./func_tests/scripts/comparator.sh ./out.tmp "$2"
then
    exit 1
fi
exit 0