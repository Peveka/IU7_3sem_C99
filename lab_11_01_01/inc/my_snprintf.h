#ifndef MY_SNPRINTF_H__
#define MY_SNPRINTF_H__
#include <stdio.h>
#include <string.h>

int my_snprintf(char *restrict str, size_t n, const char *restrict format, ...);

#endif