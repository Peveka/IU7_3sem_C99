CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic
INC_DIR := inc
UNIT_DIR := unit_tests
SRC_DIR := src
CFLAGS += -Iinc
UNIT_FLAGS := -lcheck -lrt -lpthread -lm
OBJS := out/io.o out/mem_allocation.o out/mode_handler.o out/list_operations.o out/polynom_operations.o
UNIT_OBJS := out/check_main.o out/check_polynom_operations.o

all: app.exe

app.exe: $(OBJS) out/main.o
	$(CC) -o $@ $^

unit: unit_tests.exe

unit_tests.exe: $(OBJS) $(UNIT_OBJS)
	$(CC) -o $@ $^ $(UNIT_FLAGS)

out/main.o: src/main.c inc/data.h inc/errors.h inc/modes.h \
                   inc/io.h inc/mem_allocation.h inc/list_operations.h \
                   inc/polynom_operations.h inc/mode_handler.h
	$(CC) $(CFLAGS) -c $< -o $@

out/io.o: src/io.c inc/io.h inc/errors.h inc/mem_allocation.h
	$(CC) $(CFLAGS) -c $< -o $@

out/mem_allocation.o: src/mem_allocation.c inc/mem_allocation.h inc/errors.h inc/data.h
	$(CC) $(CFLAGS) -c $< -o $@

out/mode_handler.o: src/mode_handler.c inc/mode_handler.h inc/errors.h inc/modes.h \
                           inc/io.h inc/polynom_operations.h inc/list_operations.h inc/mem_allocation.h
	$(CC) $(CFLAGS) -c $< -o $@

out/list_operations.o: src/list_operations.c inc/list_operations.h inc/data.h inc/errors.h inc/mem_allocation.h
	$(CC) $(CFLAGS) -c $< -o $@

out/polynom_operations.o: src/polynom_operations.c inc/polynom_operations.h inc/data.h inc/errors.h \
                                 inc/mem_allocation.h inc/list_operations.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_main.o: unit_tests/check_main.c
	$(CC) $(CFLAGS) -c $< -o $@

out/check_polynom_operations.o: unit_tests/check_polynom_operations.c inc/polynom_operations.h inc/data.h \
                                       inc/mem_allocation.h inc/list_operations.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean test all unit
clean:
	rm -rf out/*.o *.exe

test: unit_tests.exe
	./unit_tests.exe