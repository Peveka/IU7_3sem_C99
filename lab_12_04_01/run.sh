#!/bin/bash

if [ "$1" = "func" ]; then
    make app -s
    if [ -f "./func_tests/scripts/func_tests.sh" ]; then
        if [ "$2" = "-v" ]; then
            ./func_tests/scripts/func_tests.sh -v
        else
            ./func_tests/scripts/func_tests.sh
        fi
    else
        echo "Ошибка: func_tests.sh не найден"
        exit 1
    fi

elif [ "$1" = "unit" ]; then
    make unit_tests -s|| exit 1
    LD_LIBRARY_PATH="./libs:$LD_LIBRARY_PATH" ./unit_tests.exe

elif [ "$1" = "static" ] || [ "$1" = "dynamic" ] || [ "$1" = "dl" ]; then
    VERSION="$1"
    shift
    
    if [ "$#" -lt 2 ]; then
        echo "Ошибка: нужно минимум 2 аргумента (входной и выходной файлы)"
        echo "Пример: $0 $VERSION input.txt output.txt"
        exit 1
    fi
    
    make $VERSION -s || exit 1
    
    if [ "$VERSION" = "static" ]; then
        ./app_static.exe "$@"
    elif [ "$VERSION" = "dynamic" ]; then
        LD_LIBRARY_PATH="./libs:$LD_LIBRARY_PATH" ./app_dynamic.exe "$@"
    elif [ "$VERSION" = "dl" ]; then
        LD_LIBRARY_PATH="./libs:$LD_LIBRARY_PATH" ./app_dl.exe "$@"
    fi

else
    echo "Использование:"
    echo "  $0 func [-v]           - запустить функциональные тесты"
    echo "  $0 unit                - запустить unit-тесты"
    echo "  $0 static <args>       - запустить статическую версию"
    echo "  $0 dynamic <args>      - запустить динамическую версию"
    echo "  $0 dl <args>           - запустить версию с динамической загрузкой"
    echo ""
    echo "Примеры:"
    echo "  $0 func"
    echo "  $0 func -v"
    echo "  $0 unit"
    echo "  $0 static input.txt output.txt"
    echo "  $0 dynamic input.txt output.txt"
    echo "  $0 dl input.txt output.txt"
fi