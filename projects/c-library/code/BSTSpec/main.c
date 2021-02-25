#include <stdio.h>
#include <stdlib.h>


#include "BST_int.h"
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"


#include <time.h>
int main(int args, char** argv){

    srand(time(NULL));
    ezTreeNode_t* root = NULL;

    for(int i = 0; i != 10; i++){

        int num = rand()%10;
        //int num = ins[i];

        ezTreeNode_t* tmp = new_treeNode(num);

        if(root == NULL) root = tmp;
        else insertNode((treeNode_t*)root, (treeNode_t*)tmp, greater);

        printf("num : %d\n", num);
    }

    inOrder((treeNode_t*)root, print);printf("\n");

    for(int i = 0; i != 10; i++){
        int num = rand()%10;
        //int num = era[i];

        printf("delete : %d \n", num);

        ezTreeNode_t* tmp = (ezTreeNode_t*)deleteNode((treeNode_t**)&root, &num, greater_key_node, swap_node);
        while(tmp){

            free(tmp);
            tmp = (ezTreeNode_t*)deleteNode((treeNode_t**)&root, &num, greater_key_node, swap_node);

        }
            inOrder((treeNode_t*)root, print);printf("\n");

    }

}
