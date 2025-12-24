#ifndef STRUCT_SEARCH_H__
#define STRUCT_SEARCH_H__

#include "data.h"
#include "errors.h"

error_t search_string(item_t *items, int count, const char *prefix);

#endif