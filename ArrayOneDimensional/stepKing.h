#ifndef STEPKING_H
#define STEPKING_H

    /* The stroke function of the lame king: */
//  arrayField - This is array field,
//  countLines - The number of lines in the field,
//  start - The initial position of the figure, 
//  finish - The final position of the figure.
void step(int *arrayField, int countLines, int start, int finish);
 
    /* Checking an item to the extreme: */
//  currStr - The string of the item to check,
//  element - Checked item.
int idxCheck(int currStr, int element);

    /* Searches for the string of the specified item: */
//  arrayField - This is array field,
//  countLines - The number of lines in the field,
//  element - The line item of which we are looking for.
int searchStrEl(int *arrayField, int countLines, int element);

#endif // STEPKING_H
