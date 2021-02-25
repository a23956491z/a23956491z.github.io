#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "BST_int.h"


void print(void* a){
    if(!a) {
        printf("print NONE!\n");
        return;
    }
    printf("%d ", ((ezTreeNode_t*)a)->data);
}

ezTreeNode_t* new_treeNode(int data){

    ezTreeNode_t* tmp = (ezTreeNode_t*)malloc(sizeof(ezTreeNode_t));
    tmp->data = data;
    tmp->node.left = NULL;
    tmp->node.right = NULL;

    return tmp;
}
void* copy_treeNode(void *old){

    ezTreeNode_t* tmp = (ezTreeNode_t*)malloc(sizeof(ezTreeNode_t));
    tmp->data = ((ezTreeNode_t*)old)->data;
    tmp->node.left = NULL;
    tmp->node.right = NULL;

    return tmp;
}

/* compare Node*/
int greater(void* a, void* b){

    int data_a = ((ezTreeNode_t*)a)->data;
    int data_b = ((ezTreeNode_t*)b)->data;
    if(data_a > data_b) return 1;
    if(data_a == data_b) return 0;
    return -1;
}

int greater_key_node(void* key, void* node){
    int data_node = ((ezTreeNode_t*)node)->data;
    int key_value = *((int*)key);

    if(key_value > data_node) return 1;
    if(key_value < data_node) return -1;
    return 0;
}


void swap_node(void* a, void* b){
    ezTreeNode_t *node_a = (ezTreeNode_t*)a;
    ezTreeNode_t *node_b = (ezTreeNode_t*)b;

    int tmp = node_a->data;
    node_a->data = node_b->data;
    node_b->data = tmp;
}
