# Компилятор
CC := gcc

# Параметры компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic
SRC_DIR := src 
INC_DIR := inc
UNIT_DIR := unit_tests
OUT_DIR := out

# Добавляем путь к заголовочным файлам
CFLAGS += -Iinc

# Флаги для unit-тестов
UNIT_FLAGS := -lrt -lcheck -lpthread -lm

# Основные объектные файлы
OBJS := out/file_funcs.o out/filter.o out/mode.o out/sort.o

# Цели по умолчанию
all: app.exe unit_tests.exe

# Основная программа
app.exe: $(OBJS) out/main.o
	$(CC) -o app.exe $^

out/main.o: src/main.c inc/errors.h inc/file_funcs.h inc/mode.h inc/filter.h
	$(CC) $(CFLAGS) -c src/main.c -o out/main.o

out/file_funcs.o: src/file_funcs.c inc/file_funcs.h inc/errors.h
	$(CC) $(CFLAGS) -c src/file_funcs.c -o out/file_funcs.o

out/filter.o: src/filter.c inc/filter.h inc/sort.h inc/errors.h
	$(CC) $(CFLAGS) -c src/filter.c -o out/filter.o

out/sort.o: src/sort.c inc/sort.h
	$(CC) $(CFLAGS) -c src/sort.c -o out/sort.o

out/mode.o: src/mode.c inc/mode.h
	$(CC) $(CFLAGS) -c src/mode.c -o out/mode.o

# Unit-тесты
UNIT_OBJS := out/check_main.o out/check_filter.o out/check_sort.o
UNIT_OBJS += $(filter-out out/main.o, $(OBJS))

unit_tests.exe: $(UNIT_OBJS)
	$(CC) -o unit_tests.exe $^ $(UNIT_FLAGS)

out/check_main.o: $(UNIT_DIR)/check_main.c inc/check_filter.h inc/check_sort.h
	$(CC) $(CFLAGS) -c $(UNIT_DIR)/check_main.c -o out/check_main.o

out/check_filter.o: $(UNIT_DIR)/check_filter.c inc/check_filter.h
	$(CC) $(CFLAGS) -c $(UNIT_DIR)/check_filter.c -o out/check_filter.o

out/check_sort.o: $(UNIT_DIR)/check_sort.c inc/check_sort.h
	$(CC) $(CFLAGS) -c $(UNIT_DIR)/check_sort.c -o out/check_sort.o


# Очистка
.PHONY: clean
clean:
	rm -rf out/*.o out/*.d *.exe