#ifndef ERR_H__
#define ERR_H__

typedef enum
{
    OK = 0,
    ERR_MEM_ALLOC,
    ERR_INPUT_DATA,
    ERR_ARGS_DATA,
    ERR_INVALID_MODE,
    ERR_INVALID_DATA,
    ERR_CONST_DDX
} error_t;

#endif