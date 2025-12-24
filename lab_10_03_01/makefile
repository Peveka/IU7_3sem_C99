CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic

SRC_IMPL_1 := associative_array_impl_1.c list_operations.c mem_allocation.c
OBJ_IMPL_1 := $(SRC_IMPL_1:.c=.o)

UNIT_SRC := check_main.c check_associative_array.c
UNIT_OBJ := $(UNIT_SRC:.c=.o)

.PHONY: all unit clean

all: unit_tests.exe

unit_tests.exe: $(OBJ_IMPL_1) $(UNIT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lcheck -lm -lrt -lpthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

unit: unit_tests.exe

clean:
	rm -f $(OBJ_IMPL_1) $(UNIT_OBJ) unit_tests.exe

associative_array_impl_1.o: associative_array.h list.h mem_allocation.h
list_operations.o: associative_array.h list.h mem_allocation.h
mem_allocation.o: associative_array.h list.h mem_allocation.h
check_associative_array.o: associative_array.h
check_main.o: check_associative_array.h