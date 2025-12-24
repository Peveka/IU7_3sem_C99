CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic

SRCS := src/my_snprintf.c src/string_print_functions.c src/notation_translators.c
OBJS := $(SRCS:src/%.c=out/%.o)

UNIT_FLAGS := -lcheck -lrt -lpthread -lm
UNIT_SRCS := unit_tests/check_my_snprintf.c unit_tests/check_main.c
UNIT_OBJS := $(UNIT_SRCS:unit_tests/%.c=out/%.o)

.PHONY: all unit clean

all: unit_tests.exe

unit_tests.exe: $(OBJS) $(UNIT_OBJS)
	$(CC) $(CFLAGS) -Iinc $^ -o $@ $(UNIT_FLAGS)
	
out/%.o: src/%.c
	$(CC) $(CFLAGS) -Iinc -c $< -o $@

out/%.o: unit_tests/%.c
	$(CC) $(CFLAGS) -Iinc -c $< -o $@

clean:
	rm -rf out *.exe

out/my_snprintf.o: inc/my_snprintf.h inc/notation_translators.h
out/string_print_functions.o: inc/string_print_functions.h inc/notation_translators.h
out/check_my_snprintf.o: inc/my_snprintf.h inc/notation_translators.h
out/notation_translators.o: inc/notation_translators.h