#ifndef MEM_H__
#define MEM_H__
#include <stdio.h>
#include "errors.h"

error_t allocate_memory_with_check(size_t size,  void **arr_ptr);
void free_memory(void **ptr);

#endif