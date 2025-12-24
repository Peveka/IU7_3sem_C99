#include <stdlib.h>
#include "data.h"
#include "errors.h"

error_t node_alloc(polynom_t **node)
{
    error_t rc = OK;
    *node = malloc(sizeof(polynom_t));
    if (*node == NULL)
        rc = ERR_MEM_ALLOC;

    return rc;
}

error_t polynome_free(polynom_t **head)
{
    if (!head)
        return ERR_ARGS_DATA;
        
    polynom_t *current_node = *head;
    while (current_node != NULL)
    {
        polynom_t *should_free_node_ptr = current_node;
        current_node = current_node->next;
        free(should_free_node_ptr);
    }
    *head = NULL;

    return OK;
}

error_t alloc_coef_array(int **coeffs_arr, int data_count)
{
    error_t rc = OK;
    *coeffs_arr = calloc(data_count, sizeof(int));
    if (*coeffs_arr == NULL)
        rc = ERR_MEM_ALLOC;
    
    return rc;
}

void free_coef_data(int **coef_arr)
{
    if (coef_arr && *coef_arr != NULL)
    {
        free(*coef_arr);
        *coef_arr = NULL;
    }  
}