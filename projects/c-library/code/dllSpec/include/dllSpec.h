#ifndef DOUBLELINK_H_INCLUDED
#define DOUBLELINK_H_INCLUDED

#define false 0
#define true 1

typedef struct node {
          struct node * prev;
          struct node * next;
       } dllNode_t;



void DLL_init(dllNode_t * head); //建構一個空的 list

int DLL_isEmpty(dllNode_t *head); // head 是否為空的list

dllNode_t * DLL_next_node(dllNode_t * node); //(下一個節點)

dllNode_t * DLL_prev_node(dllNode_t * node); //(上一個節點)

unsigned int DLL_num_nodes(dllNode_t *head); //計算List中有幾個node

void DLL_add_before(dllNode_t * new_node, dllNode_t * head); //(將新node加入到head node的前一個)

void DLL_add_tail(dllNode_t * new_node, dllNode_t * head); //(將新node加入到head node的後一個)

void DLL_delete(dllNode_t * node); //(從node所在的 Linked List 中刪除此點)

void DLL_concate(dllNode_t *firstList, dllNode_t * secondList); //(將secondList 串在firstList之後)

#endif // DOUBLELINK_H_INCLUDED
