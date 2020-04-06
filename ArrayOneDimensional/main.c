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
    int i, start, finish, countLines, x, countElements, *arrayField;

    printf("Enter the number of lines in the field:\n");
    if(!(scanf("%d", &countLines)) || !countLines) {
        printf("Invalid row count\n");
        return 1;
    }

    // Total items on the field
    countElements = countLines*countLines;

    printf("Enter the START position (1 to %d):\n", countElements);
    if(!(scanf("%d", &start)) || start <= 0 || start > countElements) {
        printf("Invalid start position\n");
        return 1;
    }

    printf("Enter the END position:\n");
    if(!(scanf("%d", &finish)) || finish <= 0 || finish > countElements) {
        printf("Invalid end position\n");
        return 1;
    }
    start -= 1;
    finish -= 1;

    // Memory allocation for field numbers
    if(!(arrayField = (int*)malloc(countElements * sizeof(int)))) {
        printf("Memory isn't allocated\n");
        return 1;
    }
    // Filling the field with numbers
    x = 0;
    for (i = 0; i < countElements; i++) 
        arrayField[i] = ++x;

    step(arrayField,countLines,start,finish);

    // Cleaning memory
    free(arrayField);
    return 0;
}
