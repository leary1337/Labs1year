#include "stepKing.h"
#include <stdio.h>
#include <stdlib.h>

// Searches for the string of the specified item
int searchStrEl(int *arrayField, int countLines, int element) {
    int i, str, indRight, indLeft;

    for(i = 0; i <= countLines; i++) {
        indRight = i*i-1;
        indLeft = (i-1)*(i-1);
        
        if(element >= indLeft && element <= indRight)
            str = i;
    }

    return str;
}

// Checking an item to the extreme
int idxCheck(int currStr, int element) {
    int index;

    index = (currStr-1)*(currStr-1);
    
    // Check for leftmost
    if(index == element)
        return 1;
    
    // Check for the rightmost
    index += (currStr-1)*2;
    if(index == element)
        return 2;

    // This is not an extreme element
    return 0;    
}

// The stroke function of the lame king
void step(int *arrayField, int countLines, int start, int finish) {
    int strFinish, currStr;

    printf("%d ", arrayField[start]);
    strFinish = searchStrEl(arrayField, countLines, finish);

    currStr = searchStrEl(arrayField, countLines, start);
    if(currStr == strFinish) {
        if(start == finish)
            return;

        if(start < finish)
            step(arrayField, countLines, ++start, finish);

        if(start > finish)
            step(arrayField, countLines, --start, finish);
    }
    if(currStr < strFinish) {
        start += currStr*2;
        currStr++;
        step(arrayField, countLines, start, finish);
    }
    if(currStr > strFinish) {
        if(idxCheck(currStr, start) == 1) {
            start++;
            printf("%d ", arrayField[start]);
        }
        
        if(idxCheck(currStr, start) == 2) {
            start--;
            printf("%d ", arrayField[start]);
        }        

        currStr--;
        start -= currStr*2;
        step(arrayField, countLines, start, finish);
    }
}
