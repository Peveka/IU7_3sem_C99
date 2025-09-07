#ifndef DATA_H__

#define DATA_H__

#define MAX_AR_LEN   15
#define MAX_NAME_LEN 25
#define MAX_LINE_LEN 100

typedef struct
{
    char name[MAX_NAME_LEN];
    double volume;
    double weight;
} item_t;

#endif