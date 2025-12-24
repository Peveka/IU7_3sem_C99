#include "data.h"
#include "errors.h"
#include "modes.h"
#include "io.h"
#include "string.h"
#include "polynom_operations.h"
#include "list_operations.h"
#include "mem_allocation.h"
#include <stdlib.h>

error_t define_mode(modes_t *mode)
{
    char mode_str[MAX_MODE_LEN];
    error_t rc = scan_mode(mode_str);
    if (rc == OK)
    {
        if (strcmp(mode_str, "val") == 0)
            *mode = VAL_MODE;
        else if (strcmp(mode_str, "ddx") == 0)
            *mode = DDX_MODE;
        else if (strcmp(mode_str, "dvd") == 0)
            *mode = DVD_MODE;
        else if (strcmp(mode_str, "sum") == 0)
            *mode = SUM_MODE;
        else
            rc = ERR_INVALID_MODE;
    }
        
    return rc;
}

error_t ddx_mode_handler(polynom_t **polynome)
{
    int *polynom_coeffs = NULL;
    int *ddx_polynom_coeffs = NULL;
    int polynome_size = 0;
    
    error_t rc = scan_polynome_coefficients(&polynom_coeffs, &polynome_size);
    
    if (rc == OK)
        rc = create_polynom(polynome, polynom_coeffs, polynome_size);
        
    if (rc == OK)
        rc = ddx_polynome(*polynome, &ddx_polynom_coeffs, &polynome_size);
    
    if (rc == OK)
        rc = output_polynome_coeffs(ddx_polynom_coeffs, polynome_size);

    free_coef_data(&polynom_coeffs);
    free_coef_data(&ddx_polynom_coeffs);
    polynome_free(polynome);
    
    return rc;
}

error_t val_mode_handler(polynom_t **polynome)
{
    int *polynom_coeffs = NULL;
    int polynome_size = 0;
    int a = 0;
    int result = 0;
    
    error_t rc = scan_polynome_coefficients(&polynom_coeffs, &polynome_size);
    
    if (rc == OK)
        rc = scan_evaluate_value(&a);
        
    if (rc == OK)
        rc = create_polynom(polynome, polynom_coeffs, polynome_size);
        
    if (rc == OK)
        rc = evaluate_polynome(&result, *polynome, a);
        
    if (rc == OK)
        output_evaluate_value(result);

    free_coef_data(&polynom_coeffs);
    polynome_free(polynome);
    
    return rc;
}

error_t sum_mode_handler(polynom_t **polynome)
{
    int *first_coeffs = NULL, *second_coeffs = NULL, *result_coeffs = NULL;
    int first_size = 0, second_size = 0, result_size = 0;
    polynom_t *first_poly = NULL, *second_poly = NULL;
    
    error_t rc = scan_polynome_coefficients(&first_coeffs, &first_size);
    
    if (rc == OK)
        rc = scan_polynome_coefficients(&second_coeffs, &second_size);
        
    if (rc == OK)
        rc = create_polynom(&first_poly, first_coeffs, first_size);
        
    if (rc == OK)
        rc = create_polynom(&second_poly, second_coeffs, second_size);
        
    if (rc == OK)
        rc = polynome_add(first_poly, second_poly, &result_coeffs, &result_size);
        
    if (rc == OK)
        rc = output_polynome_coeffs(result_coeffs, result_size);

    free_coef_data(&first_coeffs);
    free_coef_data(&second_coeffs);
    free_coef_data(&result_coeffs);
    polynome_free(&first_poly);
    polynome_free(&second_poly);
    
    return rc;
}

error_t dvd_mode_handler(polynom_t **polynome)
{
    int *polynom_coeffs = NULL;
    int polynome_size = 0;
    int *even_coeffs = NULL, *odd_coeffs = NULL;
    int even_size = 0, odd_size = 0;
    
    error_t rc = scan_polynome_coefficients(&polynom_coeffs, &polynome_size);
    
    if (rc == OK)
        rc = create_polynom(polynome, polynom_coeffs, polynome_size);
        
    if (rc == OK)
        rc = divide_polynome(*polynome, &even_coeffs, &even_size, &odd_coeffs, &odd_size);
        
    if (rc == OK)
    {
        rc = output_polynome_coeffs(even_coeffs, even_size);
        if (rc == OK)
            rc = output_polynome_coeffs(odd_coeffs, odd_size);
    }

    free_coef_data(&polynom_coeffs);
    free_coef_data(&even_coeffs);
    free_coef_data(&odd_coeffs);
    polynome_free(polynome);
    
    return rc;
}