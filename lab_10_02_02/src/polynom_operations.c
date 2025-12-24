#include <stdlib.h>
#include "data.h"
#include "errors.h"
#include "mem_allocation.h"
#include "list_operations.h"


error_t create_polynom(polynom_t **polynome, int *coef_arr, int coef_arr_len)
{
    if (!polynome || !coef_arr || coef_arr_len <= 0)
        return ERR_ARGS_DATA;

    error_t rc = OK;
    *polynome = NULL;
    
    for (int i = 0; rc == OK && i < coef_arr_len; ++i)
    {
        polynom_t *node = NULL;
        rc = create_node(&node, coef_arr[i]);
        if (rc == OK)
            rc = add_node(polynome, node);
    }
    return rc;
}

error_t evaluate_polynome(int *result, polynom_t *polynome, int a)
{
    if (!result || !polynome)
        return ERR_ARGS_DATA;
        
    error_t rc = OK;
    *result = 0;
    polynom_t *current_node = polynome;
    
    while (current_node != NULL)
    {
        *result = (*result) * a + current_node->degree_value;
        current_node = current_node->next;
    }
    
    return rc;
}

error_t polynome_add(polynom_t *first_polynome, polynom_t *second_polynome, int **result_coeffs, int *result_size)
{
    if (!first_polynome || !second_polynome || !result_coeffs || !result_size)
        return ERR_ARGS_DATA;
        
    int first_size = calculate_list_size(first_polynome);
    int second_size = calculate_list_size(second_polynome);
    *result_size = (first_size > second_size) ? first_size : second_size;
    
    error_t rc = alloc_coef_array(result_coeffs, *result_size);
    if (rc == OK)
    {       
        for (int i = 0; i < *result_size; i++)
            (*result_coeffs)[i] = 0;

        polynom_t *current = first_polynome;
        for (int i = 0; i < first_size; i++)
        {
            int index = i + (*result_size - first_size);
            (*result_coeffs)[index] += current->degree_value;
            current = current->next;
        }
        current = second_polynome;
        for (int i = 0; i < second_size; i++)
        {
            int index = i + (*result_size - second_size);
            (*result_coeffs)[index] += current->degree_value;
            current = current->next;
        }
    }
    
    return rc;
}

error_t ddx_polynome(polynom_t *polynome, int **ddx_coefs, int *polynome_size)
{
    if (!polynome || !ddx_coefs || !polynome_size || *polynome_size < 0)
        return ERR_INVALID_DATA;
        
    *polynome_size = calculate_list_size(polynome);
    int original_size = *polynome_size;
    error_t rc = OK;
    int is_single_polynome = 0;
    if (original_size == 1)
    {
        *ddx_coefs = NULL;
        is_single_polynome = 1;
    }
    if (rc == OK && !is_single_polynome)
        rc = alloc_coef_array(ddx_coefs, (*polynome_size) - 1);
    if (rc == OK && !is_single_polynome)
    {
        int current_degree = *polynome_size - 1;
        polynom_t *current_polynome_degree = polynome;

        for (int i = 0; i < *polynome_size - 1; ++i)
        {
            (*ddx_coefs)[i] = current_polynome_degree->degree_value * current_degree;
            current_degree--;
            current_polynome_degree = current_polynome_degree->next;
        }
    }
    
    *polynome_size = original_size - 1;

    return rc;
}

error_t divide_polynome(polynom_t *polynome, int **even_coeffs, int *even_size, int **odd_coeffs, int *odd_size)
{
    if (!polynome || !even_coeffs || !even_size || !odd_coeffs || !odd_size)
        return ERR_ARGS_DATA;
        
    int total_size = calculate_list_size(polynome);
    *even_size = (total_size + 1) / 2;
    *odd_size = total_size / 2;
    
    error_t rc = alloc_coef_array(even_coeffs, *even_size);
    if (rc == OK)
        rc = alloc_coef_array(odd_coeffs, *odd_size);
    if (rc != OK)
        free_coef_data(even_coeffs);
    
    polynom_t *current = polynome;
    int even_idx = 0, odd_idx = 0;
    
    for (int i = 0; rc == OK && i < total_size; i++)
    {
        if ((total_size - 1 - i) % 2 == 0)
            (*even_coeffs)[even_idx++] = current->degree_value;
        else 
            (*odd_coeffs)[odd_idx++] = current->degree_value;
        current = current->next;
    }

    return rc;
}