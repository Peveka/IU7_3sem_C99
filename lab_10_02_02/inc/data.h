#ifndef DATA_H__
#define DATA_H__

struct node_t
{
    int degree_value;
    struct node_t *next;
};

typedef struct node_t polynom_t;

#endif