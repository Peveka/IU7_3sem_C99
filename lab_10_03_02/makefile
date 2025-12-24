CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic
DEBUG_FLAGS := -g3 -O0
RELEASE_FLAGS := -DNDEBUG -g0 -O2

SRC_IMPL_2 := associative_array_impl_2.c mem_allocation_darray.c darray_operations.c
OBJ_IMPL_2 := $(SRC_IMPL_2:.c=.o)

UNIT_SRC := check_main.c check_associative_array.c
UNIT_OBJ := check_main.o check_associative_array.o

.PHONY: all unit clean

all: unit_tests.exe

unit_tests.exe: $(OBJ_IMPL_2) $(UNIT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lcheck -lm -lrt -lpthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

check_main.o: check_main.c
	$(CC) $(CFLAGS) -c $< -o $@

check_associative_array.o: check_associative_array.c
	$(CC) $(CFLAGS) -c $< -o $@

unit: unit_tests.exe

clean:
	rm -f *.o *.exe

associative_array_impl_2.o: associative_array.h mem_allocation_darray.h darray.h darray_operations.h
mem_allocation_darray.o: mem_allocation_darray.h darray.h
darray_operations.o: darray_operations.h darray.h mem_allocation_darray.h
main.o: associative_array.h
check_associative_array.o: check_associative_array.h associative_array.h
check_main.o: check_associative_array.h