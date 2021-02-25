# big number functions & structs

## **List & Node**
```cpp
typedef struct Node_int {
    dllNode_t node;
    int c;

}node_int_t;

typedef struct List_int{
    node_int_t *head;
    node_int_t *rear;

    size_t size;
}list_int_t;
```
`node_int_t`用於包裝`dllNode_t` 讓Node有空間能放int
`list_int_t`是一個*list of int* 存放一連串Node的起始與尾端位址

***

## **Functions of List**
```cpp
List_int_t* list_initialize();
```
新建 List 並初始化
回傳： 該 List 的記憶體位址

```cpp
node_int_t* push_back(list_int_t* list, int value);
node_int_t* push_front(list_int_t* list, int value);
```
插入到後面，插入到前面
引數：List位址 與 待插入的整數
回傳：新增Node的位址
```cpp
void delete_list(list_int_t * list);
```
刪除整個List
引數：List位址

***

## **Functions of big number**
```cpp
list_int_t* bigNum_init( char* str, size_t size);
```
以C-style string初始化大數物件
引數：C-style string(`char[]`) 與 其長度
回傳：用來模擬大數之 List of int 的位址
```cpp
node_int_t *next_node(node_int_t *node);
node_int_t *prev_node(node_int_t *node);
```
下一個與前一個Node
```cpp
list_int_t* bigNum_add(list_int_t *, list_int_t *);
list_int_t* bigNum_multiple(list_int_t *, list_int_t *);
```

引數：大數a(List of int) 與 大數b(List of int)
回傳：建立新的大數(List of int)儲存運算結果，回傳該List地址

***

## 使用範例
```cpp
#include <stdio.h>
#include "bigNum_int.h"

int main(void){
    const int BUFFER_MAX = 256;
    char str_a[] = "891374189471897412983";
    char str_b[] = "14389135897135891375189357981";

    list_int_t *num_a = bigNum_init(str_a,  BUFFER_MAX);
    list_int_t *num_b = bigNum_init(str_b, BUFFER_MAX);
    //longer than 256 chars would be truncated

    list_int_t *result = bigNum_add(num_a, num_b);
    for(node_int_t* iter = result->head; iter != NULL; iter = next_node(iter)){
        printf("%d", iter->c);
    }printf("\n");

    delete_list(num_a), delete_list(num_b), delete_list(result);

}

```

## Main() 的輸入輸出
接收`OOOOOO * OOOOOO`以及`XXXXXX + XXXXXX`
O與X為數字，大數的位數不限，但輸入字串限制為256字元
例如：
![main.png](https://i.imgur.com/nR6qJ95.png)

***
