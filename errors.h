#ifndef ERRORS_H__
#define ERRORS_H__

typedef enum {
    OK,
    ERROR_INVALID_DATA,
    ERROR_FILE_OPEN,
    ERROR_FILE_READ,
    ERROR_FILE_NOT_EXIST,
    ERROR_EMPTY_FILE,
    ERROR_STRING_NOT_FOUND,
    ERROR_NOT_ENOUGH_ARGUMENTS,
    ERROR_NOT_ENOUGH_DATA,
    ERROR_TOO_MANY_ARGUMENTS,
    ERROR_TOO_MANY_STRINGS,
    ERROR_NAME_TOO_LONG
} error_t;

void handle_error(error_t error);

#endif