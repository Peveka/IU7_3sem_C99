#include <stdlib.h>
#include <string.h>
#include "list_struct.h"
#include "data.h"

void *alloc_elem(void)
{
    return malloc(sizeof(footballer_t));
}

void free_elem(node_t *elem)
{
    free(elem);
}

footballer_t *footballer_alloc(const char *surname, int goals_count)
{
    footballer_t *fb = alloc_elem();
    if (fb != NULL)
    {
        size_t len = strlen(surname) + 1;
        fb->surname = malloc(len);
        if (fb->surname != NULL)
        {
            strcpy((char*)fb->surname, surname);
            fb->goals_count = goals_count;
        }
        else
        {
            free_elem((node_t*)fb);
            fb = NULL;
        }
    }
    return fb;
}

void footballer_free(footballer_t *fb)
{
    if (fb != NULL)
    {
        free((void*)fb->surname);
        free_elem((node_t*)fb);
    }
}