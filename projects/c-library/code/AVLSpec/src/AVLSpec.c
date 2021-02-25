#include <stdio.h>
#include <stdlib.h>

#include "BSTSpec.h"
#include "AVLSpec.h"

#define NDBUG
#define left(n) ((AVLNode_t *)(n->node.left))
#define right(n) ((AVLNode_t *)(n->node.right))
#define dAVL_left(n) ((AVLNode_t**)&((*n)->node.left))
#define dAVL_right(n) ((AVLNode_t**)&((*n)->node.right))

#ifndef NDBUG
typedef struct intNode{
    AVLNode_t node;
    int data;
} intNode_t;
#endif

/*********** private functions***********/
static int max_int(int i, int j){
    return (i > j) ? i:j;
}

static int treeHeight(AVLNode_t *node){
    if(!node) return 0;

    node->height = max_int( treeHeight(left(node))+1,
                            treeHeight(right(node))+1);
    return node->height;
}

static int balanceFactor(AVLNode_t *node){
    if(!node) return 0;

    int left = (left(node)) ? left(node)->height : 0;
    int right = (right(node)) ? right(node)->height : 0;
    return left-right;
}

static int is_balance(AVLNode_t *node){
    if(!node) return 1;

    int res = 1;
    if(left(node)) res = is_balance(left(node));
    if(right(node)) res = is_balance(right(node)) && res;

    int bf = balanceFactor(node);
    if(res) return (bf >= -1 && bf <= 1);
    return 0;
}

static void leftRotation(AVLNode_t **origin, int print_state){
    #ifndef NDBUG
    if(print_state) printf("RR\n");
    #endif

    if(!(*origin)) return;
    AVLNode_t *node = (*origin);
    *origin = right(node);
    if(*origin){
        node->node.right = (treeNode_t*)((*origin)->node.left);
        (*origin)->node.left = (treeNode_t*)node;
    }
}
static void rightRotation(AVLNode_t **origin, int print_state){
    #ifndef NDBUG
    if(print_state) printf("LL\n");
    #endif

    if(!(*origin)) return;
    AVLNode_t *node = (*origin);
    *origin = left(node);

    if(*origin){
        node->node.left = (treeNode_t*)((*origin)->node.right);
        (*origin)->node.right = (treeNode_t*)node;
    }
}
static void AVL_LR(AVLNode_t **origin){
    #ifndef NDBUG
    printf("LR\n");
    #endif
    leftRotation( dAVL_left(origin), 0);
    rightRotation( origin, 0);
}

static void AVL_RL(AVLNode_t **origin){
    #ifndef NDBUG
    printf("RL\n");
    #endif
    rightRotation( dAVL_right(origin) , 0);
    leftRotation(  origin, 0);
}

static AVLNode_t** last_unbalanceNode(AVLNode_t **node){
    if(!node) return NULL;
    if(!(*node) || is_balance(*node)) return NULL;

    AVLNode_t **ret = NULL;
    if(!is_balance(*dAVL_left(node))){

        ret = last_unbalanceNode(dAVL_left(node));
    }
    if(!is_balance(*dAVL_right(node)) && !ret){

        ret = last_unbalanceNode(dAVL_right(node));
    }

    if(ret) return ret;
    return node;
}

static int higher(AVLNode_t *tmp){
    int h_left = ((left(tmp)) ? (left(tmp))->height : 0);
    int h_right = ((right(tmp)) ? (right(tmp))->height : 0);
    if(h_left > h_right) return -1;
    return 1;
}
void rotate(AVLNode_t **root){

    treeHeight(*root);
    AVLNode_t** unblc = last_unbalanceNode(root);

    if(unblc){
        AVLNode_t* cur = *unblc;

        if(higher(cur) == -1){
            cur = left(cur);

            if(higher(cur) == -1) rightRotation(unblc, 1);
            else AVL_LR(unblc);
        }else{
            cur = right(cur);

            if(higher(cur) == -1) AVL_RL(unblc);
            else leftRotation(unblc, 1);
        }

        treeHeight(*root);
    }
}
/*********** private functions***********/


AVLTree_t* new_tree(compare_fptr_t compare, compare_fptr_t keyNode_compare, swapKey_fptr_t swap){
    AVLTree_t* tmp = malloc(sizeof(AVLTree_t));
    tmp->root = NULL;
    tmp->compare = compare;
    tmp->keyNode_compare = keyNode_compare;
    tmp->swap = swap;
    return tmp;
}

void print_tree(AVLTree_t *tree, print_fptr_t node_print){
    if(!tree) return;

    AVLNode_t *root = (AVLNode_t *)tree->root;
    if(!root) return;

    treeHeight(root);
    inOrder((treeNode_t*)(root), node_print);
    printf("\n");
}

AVLTree_t* insert_node(AVLTree_t *tree, void *node){
    if(!node) return NULL;
    AVLNode_t** root = (AVLNode_t**)&(tree->root);

    if(tree->root) insertNode((treeNode_t*)*root, (treeNode_t*)node, tree->compare);
    else tree->root = node;

    rotate(root);
    return tree;
}

AVLNode_t* delete_node(AVLTree_t *tree, void *target){

    AVLNode_t** root = (AVLNode_t**)&(tree->root);
    if(!(*root)) return NULL;
    if(!target) return NULL;

    AVLNode_t* ret = (AVLNode_t*)deleteNode((treeNode_t **)root, target, tree->keyNode_compare, tree->swap);

    rotate(root);
    return ret;
}

#undef left
#undef right
