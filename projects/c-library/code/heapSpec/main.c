#include <stdio.h>
#include <stdlib.h>


#include "dllSpec.h"
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

void print(PQ_t *pq){
    int *arr = (int*)pq->heap.elements;
    for(int i = 0; i != pq->heap.numElements; i++){
        printf("%d ",arr[i]);
    }printf("\n");
}

int compare(void *a, void *b){
    int x = *((int*)a);
    int y = *((int*)b);
    if(x > y) return 1;
    else if(x < y) return -1;
    return 0;
}

int main(int args, char** argv){
    srand(time(NULL));

    PQ_t heap;
    createPQ(&heap, MINHEAP, sizeof(int), 10, compare);

    printf("------------------------------\n");
    printf("----------Reuse TEST----------\n");

    int arr[] = {102,8,81,15,17,22,5,9,7,24};
    int arr2[] = {12,7,16,82,13,19};
    for(int i = 0; i != 10; i++){
        Enqueue(&heap, &arr[i]);
        //printf("arr[i] : %d\n",arr[i]);
    }
        print(&heap);

    for(int i = 0; i != 7; i++){
        int tmp = *(int*)Dequeue(&heap);
        printf("POP : %d\n",tmp);
    }
    for(int i = 0; i != 6; i++){
        Enqueue(&heap, &arr2[i]);
    }
    print(&heap);

    for(int i = 0; i != 9; i++){
        int tmp = *(int*)Dequeue(&heap);
        printf("POP : %d\n",tmp);
    }

    free(heap.heap.elements);
    printf("------------------------------\n");
    printf("-----random MINHEAP below-----\n");

    int tmp_arr[32] = {0};
    createPQ(&heap, MINHEAP, sizeof(int), 32, compare);

    char str[6];

    for(int i = 0; i != 32; i++) {
        tmp_arr[i] = rand()%1000;
        Enqueue(&heap, &tmp_arr[i]);
    }
    for(int i = 0; i != 32; i++) {
        int *de = (int*)Dequeue(&heap);
        if(!de) break;
        int tmp = *de;

        itoa(tmp, str, 6);
        printf("%-5s ",str);
        if(i % 5 == 4) printf("\n");
    }printf("\n");

    free(heap.heap.elements);
    printf("------------------------------\n");
    printf("-----random MAXHEAP below-----\n");

    createPQ(&heap, MAXHEAP, sizeof(int), 32, compare);

    for(int i = 0; i != 32; i++) {
        tmp_arr[i] = rand()%1000;
        Enqueue(&heap, &tmp_arr[i]);
    }
    for(int i = 0; i != 32; i++) {
        int *de = (int*)Dequeue(&heap);
        if(!de) break;
        int tmp = *de;

        itoa(tmp, str, 6);
        printf("%-5s ",str);
        if(i % 5 == 4) printf("\n");
    }printf("\n");
}
