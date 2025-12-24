#include "sort.h"

void swap_items(void *el1, void *el2, size_t elem_size)
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
    const int *a = num1;
    const int *b = num2;
    return (*a < *b) ? -1 : (*a > *b);
}
void mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *))
{
    if (num == 0)
        return;

    size_t left = 0;
    size_t right = num - 1;
    size_t last_swap;

    while (left < right)
    {
        last_swap = left;
        for (size_t i = left; i < right; i++)
        {
            void *a = (char*)base + i * size;
            void *b = (char*)base + (i + 1) * size;
            if (compare(a, b) > 0)
            {
                swap_items(a, b, size);
                last_swap = i;
            }
        }
        right = last_swap;
        if (left >= right)
            break;

        last_swap = right;
        for (size_t i = right; i > left; i--)
        {
            void *a = (char*)base + (i - 1) * size;
            void *b = (char*)base + i * size;
            if (compare(a, b) > 0)
            {
                swap_items(a, b, size);
                last_swap = i;
            }
        }
        left = last_swap;
    }
}
