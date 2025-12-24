CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -Iinc
LDFLAGS :=
AR := ar
ARFLAGS := rcs

SRC_DIR := src
INC_DIR := inc
LIB_DIR := libs
OUT_DIR := out
UNIT_DIR := unit_tests

# Библиотека
LIB_NAME := libarrayproc
LIB_STATIC := $(LIB_DIR)/$(LIB_NAME).a
LIB_DYNAMIC := $(LIB_DIR)/$(LIB_NAME).so
LIB_OBJS := $(OUT_DIR)/array_processor.o $(OUT_DIR)/file_io.o $(OUT_DIR)/filter.o $(OUT_DIR)/sort.o

APP_OBJS := $(OUT_DIR)/main.o $(OUT_DIR)/mode.o $(OUT_DIR)/memory.o

UNIT_FLAGS := -lcheck -lm -lpthread -lrt -lsubunit # Адаптируй под OS
UNIT_OBJS := $(OUT_DIR)/check_main.o $(OUT_DIR)/check_filter.o $(OUT_DIR)/check_sort.o

all: static dynamic dl unit_tests

$(LIB_STATIC): $(LIB_OBJS) | $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

static: $(LIB_STATIC) $(APP_OBJS)
	$(CC) $(APP_OBJS) -L$(LIB_DIR) -larrayproc $(LDFLAGS) -o app_static.exe

$(LIB_DYNAMIC): $(LIB_OBJS) | $(LIB_DIR)
	$(CC) -shared $^ -o $@

dynamic: $(LIB_DYNAMIC) $(APP_OBJS)
	$(CC) $(APP_OBJS) -L$(LIB_DIR) -larrayproc $(LDFLAGS) -o app_dynamic.exe

dl: $(LIB_DYNAMIC) $(OUT_DIR)/main_dl.o $(OUT_DIR)/mode.o $(OUT_DIR)/memory.o
	$(CC) $(OUT_DIR)/main_dl.o $(OUT_DIR)/mode.o $(OUT_DIR)/memory.o -ldl $(LDFLAGS) -o app_dl.exe

unit_tests: $(LIB_STATIC) $(UNIT_OBJS)
	$(CC) $(UNIT_OBJS) -L$(LIB_DIR) -larrayproc $(UNIT_FLAGS) -o unit_tests.exe

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: $(UNIT_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR) $(LIB_DIR):
	mkdir -p $@

clean:
	rm -rf $(OUT_DIR)/*.o $(LIB_DIR)/*.a $(LIB_DIR)/*.so app_*.exe unit_tests.exe

.PHONY: all static dynamic dl unit_tests clean