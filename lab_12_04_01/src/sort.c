#include "sort.h"

static void swap_items(void *el1, void *el2, size_t elem_size)
{
    char *a = el1;
    char *b = el2;
    
    for (size_t i = 0; i < elem_size; i++)
    {
        char temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

int cmp_int(const void *num1, const void *num2)
{
    if (num1 == NULL || num2 == NULL)
        return 0;
    const int *a = num1;
    const int *b = num2;
    return (*a < *b) ? -1 : (*a > *b);
}

static size_t forward_pass(void *base, size_t left, size_t right, size_t size, compare_func_t compare)
{
    size_t last_swap = left;
    
    for (size_t i = left; i < right; i++)
    {
        void *current = (char*)base + i * size;
        void *next = (char*)base + (i + 1) * size;
        
        if (compare(current, next) > 0)
        {
            swap_items(current, next, size);
            last_swap = i; 
        }
    }
    
    return last_swap;
}

static size_t backward_pass(void *base, size_t left, size_t right, size_t size, compare_func_t compare)
{
    size_t last_swap = right;
    
    for (size_t i = right; i > left; i--)
    {
        void *previous = (char*)base + (i - 1) * size;
        void *current = (char*)base + i * size;
        
        if (compare(previous, current) > 0)
        {
            swap_items(previous, current, size);
            last_swap = i; 
        }
    }
    
    return last_swap;
}

void mysort(void *base, size_t num, size_t size, compare_func_t compare)
{
    if (num == 0 || size == 0 || compare == NULL || base == NULL)
        return;

    size_t left = 0;
    size_t right = num - 1;
    int sorting_complete = 0; 

    while (left < right && !sorting_complete)
    {
        size_t new_right = forward_pass(base, left, right, size, compare);
        size_t new_left;

        if (new_right == right)
        {
            sorting_complete = 1;
        }
        else
        {
            right = new_right;
            new_left = backward_pass(base, left, right, size, compare);
            
            if (new_left == left)
                sorting_complete = 1;
            else
                left = new_left;
        }
    }
}