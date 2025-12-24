#include "compare_functions.h"
#include "data.h"
#include <string.h>
#include <stdio.h>

int sort_footballers(const void *first, const void *second)
{
    const footballer_t *f1 = (const footballer_t*)first;
    const footballer_t *f2 = (const footballer_t*)second;
    int res = 0;
    if (f1->goals_count > f2->goals_count)
        res = -1;
    else if (f1->goals_count < f2->goals_count)
        res = 1;
    else
        res = strcmp(f1->surname, f2->surname);

    return res;
}

int footballers_eq(const void *first, const void *second)
{
    const footballer_t *first_footballer = (const footballer_t*)first;
    const footballer_t *second_footballer = (const footballer_t*)second;
    return strcmp(first_footballer->surname, second_footballer->surname) == 0 && 
        (first_footballer->goals_count == second_footballer->goals_count);
}