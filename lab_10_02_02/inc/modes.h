#ifndef MODES_H__
#define MODES_H__
#define MAX_MODE_LEN 5
#include "errors.h"
#include "data.h"

typedef enum 
{
    VAL_MODE,
    DDX_MODE,
    SUM_MODE,
    DVD_MODE
} modes_t;

#endif