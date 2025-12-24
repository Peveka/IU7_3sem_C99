#include <strings.h>
#include <string.h>
#include <stdio.h>
#include "struct_search.h"

error_t search_string(item_t *items, int count, const char *prefix)
{
    error_t found = ERROR_STRING_NOT_FOUND;
    for (int i = 0; i < count; i++)
    {
        if (strncasecmp(items[i].name, prefix, strlen(prefix)) == 0)
        {
            printf("%s\n%.6lf\n%.6lf\n", items[i].name, items[i].weight, items[i].volume);
            found = OK;
        }
    }
    return found;
}