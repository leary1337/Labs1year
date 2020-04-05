/*
*   Task: 1.3. Custom use of one-dimensional arrays
*   King, #2, field #8
*   Author: Kalabin Danil
*   Group: IVT-13BO
*/

/*  TESTS: 
* INPUT:
*   4 1 16
* OUTPUT: 
*   1 3 7 13 14 15 16
********************    
* INPUT:
*   4 16 1
* OUTPUT: 
*   16 15 9 8 4 3 1
********************
* INPUT:
*   4 1 16
* OUTPUT: 
*   1 3 7 13 14 15 16 
********************
* INPUT:
*   s
* OUTPUT: 
*   Invalid row count 
*/

#include <stdio.h> 
#include <stdlib.h>
#include "stepKing.h"

int main() {
    int i, start, finish, str, x, countEl, *A;

    printf("Enter the number of lines in the field:\n");
    if(!(scanf("%d", &str)) || !str) {
        printf("Invalid row count\n");
        return 1;
    }

    // Total items on the field
    countEl = str*str;

    printf("Enter the START position:\n");
    if(!(scanf("%d", &start)) || start <= 0 || start > countEl) {
        printf("Invalid start position\n");
        return 1;
    }

    printf("Enter the END position:\n");
    if(!(scanf("%d", &finish)) || finish <= 0 || finish > countEl) {
        printf("Invalid end position\n");
        return 1;
    }
    start -= 1;
    finish -= 1;

    // Memory allocation for field numbers
    if(!(A = (int*)malloc(countEl * sizeof(int)))) {
        printf("Memory isn't allocated\n");
        return 1;
    }
    // Filling the field with numbers
    x = 0;
    for (i = 0; i < countEl; i++) 
        A[i] = ++x;

    step(A,str,start,finish);

    free(A);
    return 0;
}
