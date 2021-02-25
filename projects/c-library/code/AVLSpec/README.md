
# 基本結構
```cpp=
typedef struct avlnode{
    treeNode_t node;
    int height;
} AVLNode_t;
```
使用時可以依照自己需求，含入(繼承)`AVLNode_t`  
例如  
```cpp
typedef struct book_node{
    avlnode node;
    int id;
    char[10] title;
    char[10] author;
    char[10] ISBN_10;
}bookNode_t;
```
---
```cpp=
typedef struct avltree{
    AVLNode_t *root;
    compare_fptr_t compare;
    compare_fptr_t keyNode_compare;
    swapKey_fptr_t swap;
} AVLTree_t;

/* typedef int (*compare_fptr_t)(void*, void*);
 * typedef void (*print_fptr_t)(void*);
 * typedef void (*swapKey_fptr_t)(void*, void*);
 */
```
**而外部自定義的Node，在使用`insert_node`時會自動被放入`AVLTree_t`**  

root可以放任何正確含入AVLNode_t的資料型別  
或是讓`insert_node`自行插入  
例如：  

```cpp
    AVLTree_t tree;
    tree.root = (AVLNode_t*)malloc(sizeof(bookNode_t))
```

# 使用方式
```cpp=
AVLTree_t* new_tree(compare_fptr_t compare, 
                    compare_fptr_t keyNode_compare, 
                    swapKey_fptr_t swap);
```
`new_tree`會回傳一個空的`AVLTree_t`，root不指向任何Node  
若暫時不指定功能函式，可以先放入`NULL`
* `compare`是比較**兩個Node**的大小，大於回傳1，等於回傳0，小於回傳-1
* `keyNode_compare`是比較**一個Node跟一個Key值**的大小，回傳方式同上
* `swap`是交換兩個Node，建議交換Node的值，而非改變連接，否則可能會有未知的錯誤
例如：
```cpp
    AVLTree_t *tree = new_tree(NULL, NULL, NULL);
```
---
```cpp=
AVLTree_t* insert_node(AVLTree_t *tree, void *node);
```
`insert_node`需要傳入一個`AVLTree_t`和自定義的Node，
也就是說，需要Node需要自行分配，
不接受僅傳入鍵值，讓`insert`自動產生Node的方式

回傳原本的`AVLTree_t`

例如：
```cpp
     
AVLNode_t* new_node(int id, char[10] title){
    bookNode_t *tmp = (bookNode_t*)malloc(sizeof(bookNode_t));
    tmp->id = id;
    strcpy(tmp->title, title);
    
    return (AVLNode_t*)tmp;
}
    
     AVLTree_t *tree = new_tree(cmp, cmp_key_node, swap);
     insert_node(tree, new_node(0, "tittle"));
```
---
```cpp=
AVLNode_t* delete_node(AVLTree_t *tree, void *key);
```
傳入一個`AVLTree_t`和有效的key值
會藉由compare函式，找出key值相等的Node並刪除

回傳原本的`AVLTree_t`

---
```cpp=
void print_tree(AVLTree_t *root, print_fptr_t print);
```