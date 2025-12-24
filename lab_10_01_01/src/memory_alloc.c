#include <stdlib.h>
#include <string.h>
#include "list_struct.h"
#include "data.h"
#include <stdio.h>

void *alloc_elem(void)
{
    return malloc(sizeof(footballer_t));
}

void free_elem(node_t *elem)
{
    free(elem);
}

node_t *node_alloc(void)
{
    return malloc(sizeof(node_t));
}

footballer_t *footballer_alloc(const char *surname, int goals_count)
{
    if (surname == NULL)
        return NULL;
    size_t len = strlen(surname) + 1;
    footballer_t *fb = alloc_elem();
    if (fb != NULL)
    {
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
        if (fb->surname != NULL) 
            free((void*)fb->surname);
            
        free_elem((node_t*)fb);
    }
}