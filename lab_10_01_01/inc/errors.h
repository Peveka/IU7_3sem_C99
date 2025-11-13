#ifndef ERRORS_H__
#define ERRORS_H__

typedef enum
{
    OK,
    ERR_NOT_ENOUGH_DATA,
    ERR_INVALID_DATA,
    ERR_MEM_ALLOC,
    ERR_FILE_OPEN
} error_t;

#endif