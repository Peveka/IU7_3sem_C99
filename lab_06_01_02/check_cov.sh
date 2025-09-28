#!/bin/bash

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")

# Поиск main файла
if [ ! -f "$dir/main.c" ]; then
    echo "No file main.c in $dir"
    exit 2
fi

# Поиск скрипта для отладки с coverage
if [ ! -f "$dir/build_debug_cov.sh" ]; then
    echo "No cov script in $dir"
    exit 2
fi

# Проверка, успешно ли собралась программа
if ! "$dir/build_debug_cov.sh"; then
    echo "Prog compiled with error"
    exit 1
fi

# Тестирование (func tests)
if ! "$dir/func_tests/scripts/func_tests.sh" > /dev/null
then 
    echo "Test failed"
    exit 1
fi

# Результат
result=$(cd "$dir" && gcov "$dir"/*.c | grep -E "^(Lines)|(File)")

echo "$result" | head -n -1

result=$(echo "$result" | tail -n 1 | grep -Eo -m 1 "[0-9]+\.[0-9]+%")
echo "Full coverage: $result"

# Проверка покрытия тестов
result="${result%%.*}"
if [ "$result" -lt 70 ]; then
    exit 1
fi