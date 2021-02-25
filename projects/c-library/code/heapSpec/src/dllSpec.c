#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "dllSpec.h"

#define loc(h, i) ((h->heap.elements) + (i * h->elementSize))
#define locs(heap, i, j) loc(heap, i), loc(heap, j)
#define parent(i) (((i-1)/2))
#define left_child(i) ((i*2+1))
#define right_child(i) ((i*2+2))
#define compare_condition (heap->pqClass==MINHEAP? -1:1)

static void swap(void *elementA, void* elementB, int elementSize){
    void * tmp= malloc(elementSize);
    memcpy(tmp,elementA,elementSize);
    memcpy(elementA,elementB,elementSize);
    memcpy(elementB,tmp,elementSize);
    free(tmp);
};

/* 建立一個 heap, 其中 pqClass為此PQ的種類(MINHEAP or MAXHEAP)，元素大小為 elementSize, 最多元數個數為 maxSize */
void createPQ(PQ_t *heap, H_class pqClass, int elementSize, int maxSize, compare_fptr cmp){

    heap->compare = cmp;
    heap->elementSize = elementSize;
    heap->heap.elements =  (void*)malloc(elementSize * maxSize);
    heap->heap.numElements = 0;
    heap->maxSize = maxSize;
    heap->pqClass = pqClass;
}

/* return 0: not empty, 1: empty*/
int IsEmpty(PQ_t *heap){
    return heap->heap.numElements==0;
}

/* return 0: not full, 1:full */
int IsFull(PQ_t *heap){
    return heap->heap.numElements==heap->maxSize;
}
static int IsValid(PQ_t *heap){
    return heap->compare && (heap->maxSize!=0);
}
static void Reheap_keyChange(PQ_t *heap, H_class type, int i){

    if(i == 0) return;

    int p = parent(i);
    int compare = heap->compare(locs(heap, i, p));

    //int i_value = *(int*)(loc(heap, i)), p_value =*(int*)(loc(heap, p));
    //printf("i : %d, parent : %d comp : %d yee: %d\n", i_value, p_value, compare,((type == MINHEAP)? (compare==-1): (compare==1)));

    if(compare == compare_condition){
        swap(locs(heap, i, p), heap->elementSize);
        Reheap_keyChange(heap, type, p);
    };
}


/* add an element into PQ */
int Enqueue(PQ_t * heap, void* elementA){

    if(!IsValid(heap)) return 0;
    if(IsFull(heap)) return 0;

    memcpy(loc(heap, heap->heap.numElements ) ,elementA, heap->elementSize);
    Reheap_keyChange(heap, heap->pqClass, heap->heap.numElements);
    heap->heap.numElements++;
    return 1;
}

static int IsValidIndex(PQ_t *heap, int i){
    return i < heap->heap.numElements;
}
/*delete an element from PQ */
void * Dequeue(PQ_t *heap){

    if(!IsValid(heap)) return NULL;
    if(IsEmpty(heap)) return NULL;

    heap->heap.numElements--;

    swap(locs(heap, 0, heap->heap.numElements), heap->elementSize);

    int i = 0;

    while(1){

//        printf("i : %d ", i);
        int right = right_child(i), left = left_child(i);
        int bigger = right;

        if(!IsValidIndex(heap, right)) {
            if(!IsValidIndex(heap, left)) break;
            bigger = left;
        }
        else if(IsValidIndex(heap, left)){
            int compare = heap->compare(locs(heap, left, right));
            bigger = (compare == (heap->pqClass==MINHEAP? -1:1)) ? left : right;
         }

        if((heap->compare(locs(heap, bigger, i)) != compare_condition)) break;

        swap(locs(heap, bigger, i), heap->elementSize);
        i = bigger;
    }


    /*
    return the address in array
    this pointer must take out it value right away
    prevent from accidentally modify the array.
    */
    return loc(heap, heap->heap.numElements);
}
