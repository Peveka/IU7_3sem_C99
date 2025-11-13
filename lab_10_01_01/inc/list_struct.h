#ifndef LIST_STRUCT_H__
#define LIST_STRUCT_H__

typedef int (*comparator_ptr)(const void*, const void*);

typedef struct node node_t;
struct node
{
    void *data;
    node_t *next;
};

#endif