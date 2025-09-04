#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "items_io.h"
#include "items_algo.h"

typedef enum { no_prefix, all, print_prefix } mode_t;

mode_t get_mode(int argc, char **argv)
{
    if (argc == 2) return no_prefix;
    if (argc == 3 && strcmp(argv[2], "ALL") == 0) return all;
    return print_prefix;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        errors_handler(NOT_ENOUGH_ARGS);
        return NOT_ENOUGH_ARGS;
    }
    if (argc > 3) {
        errors_handler(A_LOT_ARGS);
        return A_LOT_ARGS;
    }

    item_t items[MAX_AR_LEN];
    const char *filename = argv[1];
    mode_t mode = get_mode(argc, argv);

    int count = scan_struct(items, filename); 
    if (count < 0) return abs(count);

    int res = 0;
    switch (mode) {
        case print_prefix:
            return !search_items_by_prefix(items, count, argv[2]);
        case no_prefix:
            res = sort_items(items, count);
            if (res != 0) return res;
            print_struct(items, count);
            break;
        case all:
            print_struct(items, count);
            break;
    }
    return 0;
}