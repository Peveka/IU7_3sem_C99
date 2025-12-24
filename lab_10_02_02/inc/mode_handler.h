#ifndef MODE_HANDLER_H__
#define MODE_HANDLER_H__
#include "errors.h"
#include "data.h"

error_t define_mode(modes_t *mode);
error_t ddx_mode_handler(polynom_t **polynome);
error_t val_mode_handler(polynom_t **polynome);
error_t sum_mode_handler(polynom_t **polynome);
error_t dvd_mode_handler(polynom_t **polynome);

#endif