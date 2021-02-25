#ifndef BIGNUM_INT_H_INCLUDED
#define BIGNUM_INT_H_INCLUDED

#include "dllSpec.h"
#include <stdlib.h>

typedef struct Node_int {
    dllNode_t node;
    int c;

}node_int_t;

typedef struct List_int{
    node_int_t *head;
    node_int_t *rear;

    size_t size;
}list_int_t;


list_int_t* list_initialize();

node_int_t *next_node(node_int_t *node);
node_int_t *prev_node(node_int_t *node);

node_int_t* push_back(list_int_t*, int);
node_int_t* push_front(list_int_t*, int);
void delete_list(list_int_t *);

list_int_t* bigNum_init( char*, size_t);
list_int_t* bigNum_add(list_int_t *, list_int_t *);
list_int_t* bigNum_multiple(list_int_t *, list_int_t *);

#endif // BIGNUM_INT_H_INCLUDED
