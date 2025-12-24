CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -Iinc
TEST_CFLAGS := $(CFLAGS) -lcheck -lm -Iinc
OBJS := out/main.o out/matrix_io.o out/matrix_memory_handle.o out/matrix_operations.o out/mode.o out/find_inverse_matrix.o
TEST_OBJS := out/check_main.o out/check_matrix_operations.o out/check_find_inverse_matrix.o out/matrix_operations.o out/matrix_memory_handle.o out/find_inverse_matrix.o

all : app.exe

unit : unit_tests.exe

app.exe : $(OBJS)
	$(CC) $(CFLAGS) -o app.exe $^

unit_tests.exe : $(TEST_OBJS)
	$(CC) -o unit_tests.exe $^ $(TEST_CFLAGS)

out/main.o : src/main.c inc/find_inverse_matrix.h inc/matrix_memory_handle.h inc/errors.h inc/mode.h inc/matrix.h
	$(CC) $(CFLAGS) -c src/main.c -o out/main.o

out/find_inverse_matrix.o : src/find_inverse_matrix.c inc/find_inverse_matrix.h inc/matrix_memory_handle.h inc/matrix.h inc/errors.h
	$(CC) $(CFLAGS) -c src/find_inverse_matrix.c -o out/find_inverse_matrix.o

out/matrix_memory_handle.o : src/matrix_memory_handle.c inc/matrix_memory_handle.h inc/errors.h inc/matrix.h
	$(CC) $(CFLAGS) -c src/matrix_memory_handle.c -o out/matrix_memory_handle.o

out/matrix_io.o : src/matrix_io.c inc/matrix_io.h inc/matrix.h inc/errors.h inc/matrix_memory_handle.h
	$(CC) $(CFLAGS) -c src/matrix_io.c -o out/matrix_io.o

out/matrix_operations.o : src/matrix_operations.c inc/matrix_operations.h inc/errors.h inc/matrix.h
	$(CC) $(CFLAGS) -c src/matrix_operations.c -o out/matrix_operations.o

out/mode.o : src/mode.c inc/mode.h inc/errors.h inc/matrix.h inc/matrix_operations.h inc/find_inverse_matrix.h inc/matrix_io.h inc/matrix_memory_handle.h
	$(CC) $(CFLAGS) -c src/mode.c -o out/mode.o

out/check_main.o : unit_tests/check_main.c inc/check_matrix_operations.h inc/check_find_inverse_matrix.h
	$(CC) $(CFLAGS) -c unit_tests/check_main.c -o out/check_main.o

out/check_matrix_operations.o : unit_tests/check_matrix_operations.c inc/matrix_operations.h inc/matrix_memory_handle.h inc/check_matrix_operations.h
	$(CC) $(CFLAGS) -c unit_tests/check_matrix_operations.c -o out/check_matrix_operations.o

out/check_find_inverse_matrix.o : unit_tests/check_find_inverse_matrix.c inc/find_inverse_matrix.h inc/matrix_memory_handle.h inc/check_find_inverse_matrix.h
	$(CC) $(CFLAGS) -c unit_tests/check_find_inverse_matrix.c -o out/check_find_inverse_matrix.o

clean :
	rm -f out/*.o *.exe

.PHONY : all clean unit