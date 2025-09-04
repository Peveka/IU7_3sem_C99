#include <stdio.h>
#include "errors.h"

void errors_handler(error_t err) {
    switch (err) {
        case NOT_ENOUGH_ARGS:
            printf("Not enough command-line arguments!\n");
            break;
        case ERROR_FILE_OPEN:
            printf("Failed to open file!\n");
            break;
        case ERROR_FILE_READ:
            printf("Failed to read data from file!\n");
            break;
        case ERROR_INV_DATA:
            printf("Invalid data!\n");
            break;
        case ERROR_EMPTY_FILE:
            printf("File is empty!\n");
            break;
        case NOT_ENOUGH_DATA:
            printf("Not enough data in line!\n");
            break;
        case A_LOT_ARGS:
            printf("Too many command-line arguments!\n");
            break;
        case A_LOT_STR:
            printf("Too many items in file! Max is 15.\n");
            break;
        case TO_LONG_NAME:
            printf("Name of product is too long "
                   "(longer than 25 symbols)\n");
            break;
        default:
            printf("Unknown error!\n");
    }
}