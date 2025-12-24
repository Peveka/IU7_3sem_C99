CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic
SRC_DIR := src
INC_DIR := inc
UNIT_DIR := unit_tests
OUT_DIR := out

CFLAGS += -Iinc

UNIT_FLAGS := -lcheck -lrt -lpthread -lm

OBJS := out/io.o out/mem_allocate.o out/mode.o out/struct_io.o out/struct_search.o out/struct_sort.o

UNIT_OBJS := out/check_main.o out/check_struct_sort.o out/check_struct_io.o out/check_io.o

all: app.exe

app.exe: $(OBJS) out/main.o
	$(CC) -o $@ $^

unit: unit_tests.exe

unit_tests.exe: $(OBJS) $(UNIT_OBJS)
	$(CC) -o $@ $^ $(UNIT_FLAGS)

out/main.o: src/main.c inc/mode.h inc/errors.h inc/struct_io.h inc/mem_allocate.h
	$(CC) $(CFLAGS) -c $< -o $@

out/io.o: src/io.c inc/io.h inc/errors.h inc/struct.h inc/struct_sort.h
	$(CC) $(CFLAGS) -c $< -o $@

out/mem_allocate.o: src/mem_allocate.c inc/errors.h inc/data.h
	$(CC) $(CFLAGS) -c $< -o $@

out/mode.o: src/mode.c inc/mode.h inc/errors.h inc/struct_io.h inc/struct_sort.h inc/struct_search.h
	$(CC) $(CFLAGS) -c $< -o $@

out/struct_io.o: src/struct_io.c inc/data.h inc/io.h inc/errors.h inc/struct_io.h inc/struct.h inc/struct_sort.h inc/mem_allocate.h
	$(CC) $(CFLAGS) -c $< -o $@

out/struct_search.o: src/struct_search.c inc/struct_search.h
	$(CC) $(CFLAGS) -c $< -o $@

out/struct_sort.o: src/struct_sort.c inc/struct_sort.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_main.o: unit_tests/check_main.c
	$(CC) $(CFLAGS) -c $< -o $@

out/check_struct_sort.o: unit_tests/check_struct_sort.c inc/struct_sort.h inc/data.h
	@mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@

out/check_struct_io.o: unit_tests/check_struct_io.c inc/struct_io.h inc/data.h inc/errors.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_io.o: unit_tests/check_io.c inc/io.h inc/errors.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf out/*.o *.exe