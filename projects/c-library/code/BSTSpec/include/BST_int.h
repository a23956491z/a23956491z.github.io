#ifndef BST_INT_H_INCLUDED
#define BST_INT_H_INCLUDED

#define false 0
#define true 1

#include "BSTSpec.h"

typedef struct ezTree{
    treeNode_t node;
    int data;
} ezTreeNode_t;

void print(void* a);
ezTreeNode_t* new_treeNode(int data);

void* copy_treeNode(void *old);
int greater(void* a, void* b);
int greater_key_node(void* key, void* node);
void swap_node(void* a, void* b);
void* getKey(void* a);

#endif // DOUBLELINK_H_INCLUDED
