#ifndef AVL_TREE_H_INCLUDED
#define AVL_TREE_H_INCLUDED

#define false 0
#define true 1

#include "BSTSpec.h"

typedef struct avlnode{
    treeNode_t node;
    int height;
} AVLNode_t;

typedef struct avltree{
    AVLNode_t *root;
    compare_fptr_t compare;
    compare_fptr_t keyNode_compare;
    swapKey_fptr_t swap;
} AVLTree_t;

AVLTree_t* new_tree(compare_fptr_t compare, compare_fptr_t keyNode_compare, swapKey_fptr_t swap);
AVLTree_t* insert_node(AVLTree_t *tree, void *node);
AVLNode_t* delete_node(AVLTree_t *tree, void *node);

void print_tree(AVLTree_t *root, print_fptr_t print);

#endif
