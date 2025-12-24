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
UNIT_FLAGS := -lcheck -lrt -lpthread -lm

# Основные объектные файлы
OBJS := out/file_io.o out/filter.o out/mode.o out/sort.o out/memory.o out/source_data_handler.o

# Цели по умолчанию
all: app.exe unit_tests.exe

# Основная программа
app.exe: $(OBJS) out/main.o
	$(CC) -o app.exe $^

out/main.o: src/main.c inc/errors.h inc/file_io.h inc/mode.h inc/filter.h inc/source_data_handler.h
	$(CC) $(CFLAGS) -c src/main.c -o out/main.o

out/source_data_handler.o: src/source_data_handler.c inc/source_data_handler.h inc/filter.h inc/mode.h inc/errors.h
	$(CC) $(CFLAGS) -c src/source_data_handler.c -o out/source_data_handler.o

out/file_io.o: src/file_io.c inc/file_io.h inc/errors.h
	$(CC) $(CFLAGS) -c src/file_io.c -o out/file_io.o

out/filter.o: src/filter.c inc/filter.h inc/sort.h inc/errors.h
	$(CC) $(CFLAGS) -c src/filter.c -o out/filter.o

out/memory.o: src/memory.c inc/memory.h inc/errors.h
	$(CC) $(CFLAGS) -c src/memory.c -o out/memory.o

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