#include <stdio.h>
#include <stdlib.h>

#include "bigNum_int.h"

#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

void test_print(list_int_t* list, char* prefix){

    travelsal(list, prefix, '\0');
    printf("size : %d\n\n", (int)list->size);
}

int main(void){

    const int STR_LEN = 256;
    char str_num1[STR_LEN], operation_sign = '\0', str_num2[STR_LEN];

    while(scanf_s("%s %c %s" ,
            str_num1, STR_LEN, &operation_sign, STR_LEN, str_num2, STR_LEN) != EOF)
    {
        list_int_t  *num1 = bigNum_init(str_num1, STR_LEN),
                    *num2 = bigNum_init(str_num2, STR_LEN),
                    *num3;

        if(num1 == NULL || num2 == NULL){
            printf("\twrong format\n");
            continue;
        }
        switch(operation_sign){
            case '+':
                num3 = bigNum_add(num1, num2);
                break;
            case '*':
                num3 = bigNum_multiple(num1, num2);
                break;
            default:
                printf("operation sign error\n");

                delete_list(num1),delete_list(num2);
                return 0;
        }
        test_print(num3, "result : ");

        delete_list(num1),delete_list(num2),delete_list(num3);
    }

    return 0;
}
