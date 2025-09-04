#include <math.h>
#include <float.h>
#include <string.h>
#include <stdio.h>
#include "items_algo.h"
#include "errors.h"

void swap_items(item_t *a, item_t *b) {
    item_t tmp = *a;
    *a = *b;
    *b = tmp;
}

int compare_double(double a, double b, double eps) {
    if (fabs(a - b) < eps) return 0;
    return (a > b) ? 1 : -1;
}

int sort_items(item_t *items, int count) {
    for (int i = 1; i < count; ++i) {
        int k = i;
        while (k > 0) {
            if (items[k - 1].volume <= 0.0 || items[k].volume <= 0.0) {
                errors_handler(ERROR_INV_DATA);
                return ERROR_INV_DATA;
            }
            double r1 = items[k - 1].weight / items[k - 1].volume;
            double r2 = items[k].weight / items[k].volume;
            if (compare_double(r1, r2, DBL_EPSILON) > 0) {
                swap_items(&items[k - 1], &items[k]);
                --k;
            } else {
                break;
            }
        }
    }
    return 0;
}

int search_items_by_prefix(item_t *items, int count, const char *prefix) {
    int found = 0;
    size_t prefix_len = strlen(prefix);
    for (int i = 0; i < count; ++i) {
        if (strncmp(items[i].name, prefix, prefix_len) == 0) {
            printf("%s\n%.6lf\n%.6lf\n",
                   items[i].name, items[i].weight, items[i].volume);
            found = 1;
        }
    }
    return found;
}