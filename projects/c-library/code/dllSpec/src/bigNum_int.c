#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dllSpec.h"
#include "bigNum_int.h"

/*
    ***************** LIST BLOCK START  *****************
*/
list_int_t* list_initialize(){

    list_int_t * tmp = (list_int_t*)malloc(sizeof(list_int_t));
    if(tmp == NULL) return NULL;

    tmp->rear = tmp->head = NULL;
    tmp->size = 0;

    return tmp;
}

node_int_t *next_node(node_int_t *node){
    return (node_int_t*)DLL_next_node(&node->node);
}
node_int_t *prev_node(node_int_t *node){
    return (node_int_t*)DLL_prev_node(&node->node);
}

void travelsal(list_int_t* list, char* prefix, char spilt){

    if(list == NULL) return;

    char out_format[4] = "%d ";
    out_format[2] = spilt;

    printf("%s", prefix);
    for(node_int_t *iter = list->head;
        iter != NULL;
        iter = next_node(iter))
    {

        printf(out_format, iter->c);
    }
    printf("\n");
}
node_int_t* new_after(node_int_t* prev_node, int i){


    node_int_t* tmp = (node_int_t*)malloc(sizeof(node_int_t));
    if(tmp == NULL) return NULL;

    tmp->c = i;
    if(prev_node == NULL){
        DLL_init(&tmp->node);
    }else{
        DLL_add_tail(&tmp->node, &prev_node->node);
    }

    return tmp;
}
node_int_t* new_before(node_int_t* next_node, int i){


    node_int_t* tmp = (node_int_t*)malloc(sizeof(node_int_t));
    if(tmp == NULL) return NULL;

    tmp->c = i;
    if(next_node == NULL){
        DLL_init(&tmp->node);
    }else{
        DLL_add_before(&tmp->node, &next_node->node);
    }

    return tmp;
}


node_int_t* push_back(list_int_t* list, int i){

    node_int_t *tmp = new_after(list->rear, i);

    if(tmp != NULL) (list->size)++;
    if(list->head == NULL){
        list->head = tmp;
    }
    list->rear = tmp;

    return tmp;
}
node_int_t* push_front(list_int_t* list, int i){

    node_int_t *tmp = new_before(list->head, i);

    if(tmp != NULL) (list->size)++;
    if(list->rear == NULL){
        list->rear = tmp;
    }
    list->head = tmp;

    return tmp;
}

void delete_node(list_int_t *list, node_int_t *node){
    if(node == list->head){
        list->head = next_node(list->head);
    }
    if(node == list->rear){
        list->rear = next_node(list->rear);
    }
    DLL_delete(((dllNode_t*)node));

    list->size--;
}
void delete_list(list_int_t *list){

    if(list == NULL) return;
    for(node_int_t *iter = list->head; iter != NULL; ){

        node_int_t *next_iter = next_node(iter);
        DLL_delete((dllNode_t*)iter);
        iter = next_iter;
    }

    free(list);
}

/*
    ***************** LIST BLOCK ENDED  *****************
*/

/*
    ***************** BIG NUM BLOCK START  *****************
*/

list_int_t* add_padding_zero_front(list_int_t* list, size_t n){
    for(int i = 0; i != n; i ++){
        push_front(list, 0);
    }
    return list;
}
list_int_t* add_padding_zero_back(list_int_t* list, size_t n){
    for(int i = 0; i != n; i ++){
        push_back(list, 0);
    }
    return list;
}
void remove_padding_zero_front(list_int_t* list){
    while(list->head->c == 0){
        delete_node(list ,list->head);
    }
}
int char_to_int(char c){
    return c-'0';
}
list_int_t* bigNum_init( char* str, size_t n){

    unsigned long long len = strlen(str);
    if(len < n) n = len;

    list_int_t* tmp = list_initialize();

    for(int i = 0; i != n; i++){
        if(isdigit(str[i]) == false){
            delete_list(tmp);
            return 0;
        }

        push_back(tmp, char_to_int(str[i]));
    }
    if(strcmp(str ,"0")) remove_padding_zero_front(tmp);
    return tmp;
}



list_int_t* bigNum_add(list_int_t *num1, list_int_t *num2){
    if(num1->size < num2->size) return bigNum_add(num2, num1);

    list_int_t *result = bigNum_init("0", 1);
    add_padding_zero_front(result, num1->size-1);
    add_padding_zero_front(num2, num1->size - num2->size);

    for(node_int_t  *iter_1 = num1->rear, *iter_2 = num2->rear, *iter_3 = result->rear;
        iter_1 != NULL && iter_2 != NULL && iter_3 != NULL;
        iter_1 = prev_node(iter_1), iter_2 = prev_node(iter_2), iter_3 = prev_node(iter_3)
    ){
        iter_3->c = iter_2->c + iter_1->c;
        //printf("%d ", iter_3->c);
    }

    for(node_int_t *iter_3 = result->rear; iter_3 != NULL; iter_3 = prev_node(iter_3)){

        if((iter_3->c) >= 10){

            iter_3->c -= 10;
            if(iter_3 == result->head){

                add_padding_zero_front(result, 1);

                prev_node(iter_3)->c++;
                break;
            }
            prev_node(iter_3)->c++;
        }
    }
    remove_padding_zero_front(num2);
    return result;
}

list_int_t* bigNum_multiple(list_int_t *num1, list_int_t *num2){
    if(num1->size < num2->size) return bigNum_multiple(num2, num1);

    list_int_t *result = bigNum_init("0", 1);
    add_padding_zero_front(result, num1->size-1);

    for(node_int_t  *iter_2 = num2->head; iter_2 != NULL; iter_2 = next_node(iter_2)){
        for(node_int_t  *iter_1 = num1->rear, *iter_3 = result->rear;
            iter_1 != NULL && iter_3 != NULL;
            iter_1 = prev_node(iter_1), iter_3 = prev_node(iter_3))
        {
            iter_3->c = iter_3->c + iter_2->c * iter_1->c;
        }
        for(node_int_t *iter_3 = result->rear; iter_3 != NULL; iter_3 = prev_node(iter_3)){

            if(iter_3->c > 10){

                if(iter_3 == result->head){

                    add_padding_zero_front(result, 1);
                    prev_node(iter_3)->c += iter_3->c / 10;
                    iter_3->c %= 10;
                    break;
                }
                prev_node(iter_3)->c += iter_3->c / 10;
                iter_3->c %= 10;
            }
        }
        if(iter_2 != num2->rear) add_padding_zero_back(result, 1);
        //break;
    }

    return result;
}
/*
    ***************** BIG NUM BLOCK ENDED  *****************
*/
