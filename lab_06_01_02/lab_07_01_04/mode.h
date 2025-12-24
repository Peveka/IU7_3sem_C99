#ifndef MODE_H__

#define MODE_H__
#include <string.h>
#include "errors.h"

error_t args_handle(int argc);
int mode_define(int argc, char **argv);

#endif