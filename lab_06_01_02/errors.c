#include <stdio.h>
#include "errors.h"

void handle_error(error_t error)
{
    switch (error)
    {
        case ERROR_NOT_ENOUGH_ARGUMENTS:
            printf("Not enough command line arguments!\n");
            break;
        case ERROR_FILE_OPEN:
            printf("Failed to open file!\n");
            break;
        case ERROR_FILE_READ:
            printf("Failed to read data from file!\n");
            break;
        case ERROR_INVALID_DATA:
            printf("Invalid data!\n");
            break;
        case ERROR_EMPTY_FILE:
            printf("File is empty!\n");
            break;
        case ERROR_NOT_ENOUGH_DATA:
            printf("Not enough data in line!\n");
            break;
        case ERROR_TOO_MANY_ARGUMENTS:
            printf("Too many command-line arguments!\n");
            break;
        case ERROR_TOO_MANY_STRINGS:
            printf("Too many items in file! Max is 15.\n");
            break;
        case ERROR_NAME_TOO_LONG:
            printf("Name of product is too long (longer than 25 symbols)");
            break;
        case ERROR_STRING_NOT_FOUND:
            printf("Name string not found");
            break;
        default:
            printf("Unknown error!\n");
    }
}