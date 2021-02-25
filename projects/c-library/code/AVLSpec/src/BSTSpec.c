#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "BSTSpec.h"
#define NDBUG

treeNode_t* insertNode(treeNode_t* root, treeNode_t* node, compare_fptr_t compare){
    if(!root || !node) return NULL;
    if(root == node) return NULL;

    while(1){

        if(compare(node, root) == 1){
            if(root->right){
                root = root->right;
            }else{
                root->right = node;
                break;
            }
        }
        else{
            if(root->left){
                root = root->left;
            }else{
                root->left = node;
                break;
            }
        }
    }

    return node;
}
#define d_right(tmp) (&((*tmp)->right))
#define d_left(tmp) (&((*tmp)->left))

treeNode_t** findMinNode(treeNode_t** root){
    treeNode_t **tmp = root;
    while((*tmp)->left){
        tmp = &((*tmp)->left);
    }

    return tmp;
}
treeNode_t** findMaxNode(treeNode_t** root){
    treeNode_t **tmp = root;
    while((*tmp)->right){
        tmp = &((*tmp)->right);
    }

    return tmp;
}

/*
    key Node compare
*/
treeNode_t** findNode(treeNode_t** root, void* key,compare_fptr_t compare){
    treeNode_t **tmp = root;
    while(*tmp){

        int compare_result = compare(key, *tmp);

        if(compare_result == 1)         tmp =   d_right(tmp);
        else if(compare_result == -1)   tmp =   d_left(tmp);
        else return tmp;
    }
    return tmp;
}

void inOrder(treeNode_t* root, print_fptr_t print){
    if(!root)return;

    inOrder(root->left, print);
    print(root);
    inOrder(root->right, print);
}

/*
    key Node compare
*/
treeNode_t* deleteNode(treeNode_t** node, void* data, compare_fptr_t compare, swapKey_fptr_t swap){

    treeNode_t** found=  findNode(node, data, compare);
    if(*found == NULL) return NULL;

    treeNode_t *cur = *found;
    if( cur->right != NULL && cur->left != NULL){

        treeNode_t **target = &cur->left;
        target = findMaxNode(target);

        swap(*target, *found);
        cur = *target;
        *target = (*target)->left;

    }else if( cur->right != NULL){

        *found = cur->right;
    }else{

        *found = cur->left;
    }

    return cur;
}

void treeCopy(treeNode_t* source, treeNode_t** new_root, alloc_fptr_t alloc_node){

    if(!source)return;
    if(*new_root == NULL){
        *new_root = (treeNode_t*)alloc_node(source);
    }
    treeNode_t* rt = *new_root;

    if(source->left){
        rt->left = (treeNode_t*)alloc_node(source->left);
        treeCopy(source->left, &(rt->left), alloc_node);
    }
    if(source->right){
        rt->right = (treeNode_t*)alloc_node(source->right);
        treeCopy(source->right, &(rt->right), alloc_node);
    }
}

int treeEqual(treeNode_t* root_a, treeNode_t* root_b, compare_fptr_t compare){

    if(!root_a && !root_b) return 1;
    if(root_a && !root_b) return 0;
    if(compare(root_a, root_b) != 0) return 0;
    if(root_a->left) return 1&&treeEqual(root_a->left, root_b->left, compare);
    if(root_a->right)return 1&&treeEqual(root_a->right, root_b->right, compare);
    return 1;
}
