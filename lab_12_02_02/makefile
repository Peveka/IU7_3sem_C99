CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -Iinc -fPIC

SRC_DIR := src
INC_DIR := inc
LIB_DIR := libs
OUT_DIR := out

LIB_NAME := libsource
LIB_SO := $(LIB_DIR)/$(LIB_NAME).so
LIB_OBJ := $(OUT_DIR)/lib_source.o

all: $(LIB_SO)

$(LIB_SO): $(LIB_OBJ) | $(LIB_DIR)
	$(CC) -shared $^ -o $@

$(OUT_DIR)/lib_source.o: $(SRC_DIR)/lib_source.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(LIB_SO)
	python3 app.py

clean:
	rm -rf $(OUT_DIR)/*.o $(LIB_DIR)/*.so

.PHONY: all run clean info