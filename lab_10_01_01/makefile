CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -Iinc
TEST_CFLAGS := $(CFLAGS) -lcheck -lm -Iinc
OBJS := out/main.o out/compare_functions.o out/args_handler.o out/file_io.o out/list_sort.o out/memory_alloc.o out/operations_with_elem.o out/operations_with_list.o
CHECK_OBJS_SRC = out/check_operations_with_elem.o out/check_operations_with_list.o
CHECK_OBJS = $(CHECK_OBJS_SRC) $(filter-out out/main.o,$(OBJS))

all : app.exe

app.exe : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

unit_tests.exe: $(CHECK_OBJS)
	$(CC) $^ -o $@ $(TEST_CFLAGS)

out/main.o : src/main.c inc/data.h inc/errors.h inc/list_struct.h inc/operations_with_list.h inc/file_io.h inc/list_sort.h inc/args_handler.h inc/compare_functions.h
	$(CC) $(CFLAGS) -c $< -o $@

out/compare_functions.o : src/compare_functions.c inc/data.h inc/compare_functions.h
	$(CC) $(CFLAGS) -c $< -o $@

out/args_handler.o : src/args_handler.c inc/errors.h
	$(CC) $(CFLAGS) -c $< -o $@

out/file_io.o : src/file_io.c inc/errors.h inc/list_struct.h inc/data.h inc/errors.h inc/operations_with_elem.h inc/operations_with_list.h
	$(CC) $(CFLAGS) -c $< -o $@

out/list_sort.o : src/list_sort.c inc/errors.h inc/alloc_memory.h inc/list_struct.h
	$(CC) $(CFLAGS) -c $< -o $@

out/memory_alloc.o : src/memory_alloc.c inc/list_struct.h inc/data.h
	$(CC) $(CFLAGS) -c $< -o $@

out/operations_with_elem.o : src/operations_with_elem.c inc/list_struct.h inc/errors.h
	$(CC) $(CFLAGS) -c $< -o $@

out/operations_with_list.o : src/operations_with_list.c inc/list_struct.h inc/data.h inc/alloc_memory.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_operations_with_elem.o : unit_tests/check_operations_with_elem.c inc/errors.h inc/list_struct.h inc/operations_with_elem.h inc/operations_with_list.h inc/data.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_operations_with_list.o : unit_tests/check_operations_with_list.c inc/errors.h inc/list_struct.h inc/operations_with_elem.h inc/operations_with_list.h inc/compare_functions.h inc/data.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f out/*.o *.exe

.PHONY : all clean