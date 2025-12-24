#include <math.h>
#include <float.h>
#include "struct_sort.h"
#define EPSL 2.220446049250313080847e-16

int compare_double(double a, double b, double epsilon)
{
    int res = 0;
    if (fabs(a - b) < epsilon) 
    {
        res = 0;
    }
    else
    {
        res = ((a > b) ? 1 : -1);
    }

    return res;
}

static void swap_items(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort_struct(item_t *items, int count)
{
    for (int i = 1; i < count; i++)
    {
        int should_change = 1;
        int k = i;
        for (k = i; k > 0 && should_change; --k)
        {
            double ratio1 = items[k - 1].weight / items[k - 1].volume;
            double ratio2 = items[k].weight / items[k].volume;

            if (compare_double(ratio1, ratio2, EPSL) > 0)
            {
                swap_items(&items[k - 1], &items[k]);
            }
            else
            {
                should_change = 0;
            }
        }
    }
}