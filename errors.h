#ifndef ERRORS_H
#define ERRORS_H

/*
Errors codes
*/
typedef enum {
    OK,
    ERROR_INV_DATA,
    ERROR_FILE_OPEN,
    ERROR_FILE_READ,
    ERROR_FILE_NOT_EXIST,
    ERROR_EMPTY_FILE,
    NOT_ENOUGH_ARGS,
    NOT_ENOUGH_DATA,
    A_LOT_ARGS,
    A_LOT_STR,
    TO_LONG_NAME
} error_t;

/*
Function-handler of happens errors
*/
void errors_handler(error_t err);

#endif