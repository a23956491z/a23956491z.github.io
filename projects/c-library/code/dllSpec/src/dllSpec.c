#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "dllSpec.h"

#define NTEST
/*
    ***************** DLL SPEC BLOCK START  *****************
*/
int DLL_isEmpty(dllNode_t *head){
    if(head == NULL) return 1;
    return 0;
}

void DLL_init(dllNode_t * head){

    if(DLL_isEmpty(head)) return;
    head->prev = NULL;
    head->next = NULL;
}

dllNode_t * DLL_next_node(dllNode_t * node){
    if(DLL_isEmpty(node)) return NULL;
    return node->next;
}
dllNode_t * DLL_prev_node(dllNode_t * node){
    if(DLL_isEmpty(node)) return NULL;
    return node->prev;
}

unsigned int DLL_num_nodes(dllNode_t *head){
    size_t count = 0;

    dllNode_t *p = head;
    if(p != NULL){

        #ifndef NTEST
                printf("0x%"PRIXPTR "\n", (uintptr_t)p);
        #endif

        count++;
        while(DLL_next_node(p) != NULL){

            count++;
            p = DLL_next_node(p);

            #ifndef NTEST
                printf("0x%"PRIXPTR "\n", (uintptr_t)p);
            #endif
        }
    }
    return count;
}

/*
    Only link new_node & node, doesn't allcate a new node
*/
void DLL_add_before(dllNode_t * new_node, dllNode_t * node){

    if(DLL_isEmpty(node)  || DLL_isEmpty(new_node)) return;

    new_node->prev = node->prev;
    new_node->next = node;
    if(new_node->prev != NULL){
        new_node->prev->next = new_node;
    }

    node->prev = new_node;
}

/*
    Only link new_node & node, doesn't allcate a new node
*/
void DLL_add_tail(dllNode_t * new_node, dllNode_t * node){

    if(DLL_isEmpty(node) || DLL_isEmpty(new_node)) return;

    for(; node->next != NULL; node = DLL_next_node(node));

    new_node->prev = node;
    new_node->next = node->next;
    if(new_node->next != NULL){
        new_node->next->prev = new_node;
    }

    node->next = new_node;
}

void DLL_delete(dllNode_t * node){

    if(DLL_isEmpty(node) || DLL_isEmpty(node)) return;

    if((node)->prev != NULL)
        (node)->prev->next = (node)->next;
    if((node)->next != NULL)
        (node)->next->prev = (node)->prev;

    free(node);

    return;
}

void DLL_concate(dllNode_t *firstList, dllNode_t * secondList){

    if(DLL_isEmpty(firstList) || DLL_isEmpty(secondList)) return;

    while(firstList->next != NULL){
        firstList = DLL_next_node(firstList);
    }

    while(secondList->prev != NULL){
        secondList = DLL_prev_node(secondList);
    }

    firstList->next = &*secondList;
    secondList->prev = &*firstList;
}

/*
    ***************** DLL SPEC BLOCK ENDED  *****************
*/

dllNode_t* new_node_before(dllNode_t * node){

    dllNode_t* new_node =  (dllNode_t*)malloc(sizeof(dllNode_t));

    if(node == NULL){
        node = new_node;
        DLL_init(node);
    }else{
        DLL_add_before(new_node, node);
    }
    return new_node;
}

dllNode_t* new_node_tail(dllNode_t * node){

    dllNode_t* new_node =  (dllNode_t*)malloc(sizeof(dllNode_t));

    if(node == NULL){
        node = new_node;
        DLL_init(node);
    }else{
        DLL_add_tail(new_node, node);
    }

    return new_node;
}

#ifndef NTEST

void test_node_address(dllNode_t* head, char* infor){
    printf("%s : \n",infor);
    printf("\t size : %d \n", DLL_num_nodes(head));

}

int main(int args, char** argv){

    dllNode_t* head = NULL;
    printf("list1 is empty or not : %d\n", DLL_isEmpty(head));

    head = new_node_tail(head);
    new_node_tail(head);
    new_node_tail(head);
    new_node_tail(head);

    test_node_address(head, "after 4 add tail");

    head = new_node_before(head);
    test_node_address(head, "after add before");

    dllNode_t * specific_node =   new_node_tail(head);
    test_node_address(head, "current list1");

    new_node_tail(head);
    test_node_address(head, "after add rear");

    DLL_delete(specific_node);
    test_node_address(head, "after delete");


    dllNode_t* head2 = NULL;

    head2 = new_node_tail(head2);
    head2 = new_node_before(head2);
    new_node_tail(head2);

    test_node_address(head2, "list2 node");

    DLL_concate(head, head2);
    test_node_address(head, "after concate");

    return 0;
}

#endif
