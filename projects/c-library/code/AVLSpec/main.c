#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
#include "AVLSpec.h"
#include "BSTSpec.h"
#define NDBUG

typedef struct intNode{
    AVLNode_t node;
    int data;
} intNode_t;

int node_compare(void *a, void *b){
    int int_a = ((intNode_t*)a)->data;
    int int_b = ((intNode_t*)b)->data;

    if(int_a > int_b) return 1;
    if(int_a < int_b) return -1;
    return 0;
}
int keyNode_compare(void* key, void* node){
    int data_node = ((intNode_t*)node)->data;
    int key_value = *((int*)key);

    if(key_value > data_node) return 1;
    if(key_value < data_node) return -1;
    return 0;
}
void swap_node(void* a, void* b){
    if(!a || !b) return;
    intNode_t *node_a = (intNode_t*)a;
    intNode_t *node_b = (intNode_t*)b;

    int tmp = node_a->data;
    node_a->data = node_b->data;
    node_b->data = tmp;
}

static void node_print(void *a){
    if(!a) return;
    intNode_t *node = (intNode_t*)a;
    int left = ((treeNode_t*)node)->left ? ((AVLNode_t*)((treeNode_t*)node)->left)->height : 0;
    int right = ((treeNode_t*)node)->right ? ((AVLNode_t*)((treeNode_t*)node)->right)->height : 0;

    printf("\tdata: %d ", node->data);
    printf("h: %d bf: %d", node->node.height, left-right);
    printf("\n");
}

intNode_t *new_fucking_int_node(int num){
    intNode_t* tmp = malloc(sizeof(intNode_t));
    if(!tmp) return NULL;
    ((treeNode_t*)tmp)->left = NULL;
    ((treeNode_t*)tmp)->right = NULL;
    ((AVLNode_t*)tmp)->height = 0;
    tmp->data = num;

    return tmp;
}

int main(int args, char** argv){

        srand(time(NULL));
        AVLTree_t* tree = new_tree(node_compare, keyNode_compare, swap_node);

        int test_ll[10] = {1,2,1,4,4,4,0,2,4,4};
        for(int i = 0; i != 10; i++){

            int num = test_ll[i];
            num = rand()%5;

            printf("num : %d\n", num);
            if(!insert_node(tree, new_fucking_int_node(num))) break;

            #ifndef NDBUG
            print_tree(tree, node_print);
            #endif
        }

        print_tree(tree, node_print);

        for(int i = 0; i != 5; i++){

            int num = rand()%5;
            printf("del : %d\n", num);

            AVLNode_t *ret = delete_node(tree, &num);
            if(ret) free(ret);

            #ifndef NDBUG
            print_tree(tree, node_print);
            #endif
        }
        print_tree(tree, node_print);

        printf("\nYEAH BABY\n");
}
