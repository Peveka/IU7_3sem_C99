#ifndef ITEMS_ALGO_H
#define ITEMS_ALGO_H

#include "items_io.h"

/**
 * @brief Insert sort by density
 * @return 0 - OK, else - code error
 */
int sort_items(item_t *items, int count);

/**
 * @brief search items by prefix (case sensitive)
 * @return 1 - found, 0 - not found
 */
int search_items_by_prefix(item_t *items, int count, const char *prefix);

#endif 