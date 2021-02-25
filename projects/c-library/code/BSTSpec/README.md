# Binary Search Tree functions & structs


## **Node**
```cpp=
/* default Node */
typedef struct node {
          struct node * left;
          struct node * right;
} treeNode_t;


```

***


## Type defines:
```cpp=
typedef int (*compare_fptr_t)(void*, void*);
typedef void (*print_fptr_t)(void*);
typedef void*(*alloc_fptr_t)(void*);
typedef void (*swapKey_fptr_t)(void*, void*);
typedef void*(*getKey_fptr_t)(void*);

```
## Functions
```cpp=
/**
 * @details only link do link works,<br/>
 *            did not allocate memory inside and.
 * @param root pointer of root in the tree.
 * @param node pointer of the new node we created, <br/>
 *               which is the node we gonna put into the tree.
 * @param compare pointer of compare function which could "compare 2 node", <br/>
 *                we assume the form of function is <code>int func(void* a, void* b)<code/>, <br/>
 *                and the return form is when "a > b return 1", "a == b return 0", otherwise return -1.
 * @return the address of "node" we just pass in,
 *         as the node we inserted into the tree.
 * @example of compare function:
 *  int greater(void* a, void* b){
 *      int data_a = ((ezTreeNode_t*)a)->data;
 *      int data_b = ((ezTreeNode_t*)b)->data;
 *      if(data_a > data_b) return 1;
 *      if(data_a == data_b) return 0;
 *      return -1;
 *  }
 */
treeNode_t* insertNode(treeNode_t* root, treeNode_t* node, compare_fptr_t compare);

/**
 *
 * @param root pointer of any node in the tree.
 * @return the most left and downward node we found.
 */
treeNode_t* findMinNode(treeNode_t* root);

/**
 *
 * @param root pointer of any node in the tree.
 * @return the most right and downward node we found.
 */
treeNode_t* findMaxNode(treeNode_t* root);

/**
 *
 * @param root pointer of root in the tree.
 * @param key pointer of a key value which is the data inside tree node.
 * @param compare pointer of compare function which could "compare 2 node", <br/>
 *                we assume the form of function is <code>int func(void* a, void* b)<code/>, <br/>
 *                and the return form is when "a > b return 1", "a == b return 0", otherwise return -1.
 * @return the node we found that equals the key value.
 */
treeNode_t* findNode(treeNode_t* root, void* key,compare_fptr_t compare);


/**
 *
 * @param root pointer of root in the tree.
 * @param print pointer of print function which could "print a node".
 */
void inOrder(treeNode_t* root, print_fptr_t print);

/**
 *
 * @param root pointer of root in the tree
 * @param data pointer of a key value which is the data inside tree node.
 * @param compare pointer of compare function which could "compare 2 node", <br/>
 *                  we assume the form of function is <code>int func(void* a, void* b)<code/>, <br/>
 *                  and the return form is when "a > b return 1", "a == b return 0", otherwise return -1.
 * @param swap pointer of compare function which could "swap 2 node".
 * @param getKey pointer of getKey function which could "return the key of node".
 * @return return the pointer of root node
 * @example root = deleteNode(root, &i, compare, swap, getKey);
 */
treeNode_t* deleteNode(treeNode_t* root, void* data, compare_fptr_t compare, swapKey_fptr_t swap, getKey_fptr_t getKey);


/**
 *
 * @param source the pointer of source tree.
 * @param new_root the double pointer of a empty tree, we gonna put the duplicate into this.
 * @param alloc_node pointer of allocate function which could "malloc a node"<br\>
 *        and returns the pointer of new Node.
 * @example of allocate function:
 *  void* copy_treeNode(void *old){
 *
 *      ezTreeNode_t* tmp = (ezTreeNode_t*)malloc(sizeof(ezTreeNode_t));
 *      tmp->data = ((ezTreeNode_t*)old)->data;
 *      tmp->node.left = NULL;
 *      tmp->node.right = NULL;*
 *
 *  return tmp;
}
 */
void treeCopy(treeNode_t* source, treeNode_t** new_root, alloc_fptr_t alloc_node);

/**
 *
 * @param root_a root pointer of root in the tree_A
 * @param root_b root pointer of root in the tree_B
 * @param compare pointer of compare function which could "compare 2 node", <br/>
 *                  we assume the form of function is <code>int func(void* a, void* b)<code/>, <br/>
 *                  and the return form is when "a > b return 1", "a == b return 0", otherwise return -1.
 * @return 1 means equal, 0 means not equal.
 */
int treeEqual(treeNode_t* root_a, treeNode_t* root_b, compare_fptr_t compare);
```
