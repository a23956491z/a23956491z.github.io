
Heap的結構（**和原本一樣**）
```cpp
typedef struct HeapType {
    void *elements; // element array
    int numElements; // number of elements
} Heap_t;


typedef enum {
	MINHEAP=0,
	MAXHEAP=1
} H_class;

typedef int (*compare_fptr)(void*, void*);
typedef void (*assign_fptr)(void*, void*);

typedef struct PQ {
    H_class pqClass;
    Heap_t  heap;
    int elementSize;
    int maxSize;
    compare_fptr compare;
} PQ_t;
```


```cpp
/*
 * 建立一個 pq,
 * 其中 pqClass為此PQ的種類(MINHEAP or MAXHEAP)
 * 元素大小為 elementSize,
 * 最多元數個數為 maxSize
 */
void createPQ(PQ_t *pq, H_class pqClass, int elementSize, int maxSize, compare_fptr cmp);

/* return 0: not empty, 1: empty*/
int IsEmpty(PQ_t *pq);
/* return 0: not full, 1:full */
int IsFull(PQ_t *pq);
/* add an element into PQ */
int Enqueue(PQ_t * PQ, void* elementA);

/* pop an element from PQ
 * return the address of element in array
 * this pointer must take out it value right away
 * prevent from accidentally modify the array.
 */
void * Dequeue(PQ_t *PQ);
```
