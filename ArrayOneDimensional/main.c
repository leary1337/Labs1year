/*
*   Задание 1.3. Нестандартное применение одномерных массивов
*   Король, №2, поле №8
*   Калабин Данил
*   ИВТ-13БО
*/
#include <stdio.h>
#include <stdlib.h>


// Ищет в какой строке указанный элемент
int searchStrEl(int *A,int strs, int elem) {
    int i, str, indR, indL;

    for(i = 0; i <= strs; i++) {
        indR = i*i-1;
        indL = (i-1)*(i-1);
        
        if(elem >= indL && elem <= indR)
            str = i;
    }

    return str;
}

// Проверка элемента на крайность
int idxCheck(int currStr, int el) {
    int ind;

    ind = (currStr-1)*(currStr-1);
    
    // Проверка на левый крайний
    if(ind == el)
        return 1;
    
    // Проверка на правый крайний
    ind += (currStr-1)*2;
    if(ind == el)
        return 2;

    // Ни левый крайний и не правый
    return 0;    
}

// Функция хода фигуры
void step(int *A, int n, int a, int b) {
    int strFinish, currStr;

    printf("%d ", A[a]);
    strFinish = searchStrEl(A, n, b);

    currStr = searchStrEl(A, n, a);
    if(currStr == strFinish) {
        if(a == b)
            return;

        if(a < b)
            step(A,n,++a,b);

        if(a > b)
            step(A,n,--a,b);
    }
    if(currStr < strFinish) {
        a += currStr*2;
        currStr++;
        step(A,n,a,b);
    }
    if(currStr > strFinish) {
        if(idxCheck(currStr, a) == 1) {
            a++;
            printf("%d ", A[a]);
        }
        
        if(idxCheck(currStr, a) == 2) {
            a--;
            printf("%d ", A[a]);
        }        

        currStr--;
        a -= currStr*2;
        step(A,n,a,b);
    }
}

void main() {
    int i, start, finish, str, x, countEl, *A;

    printf("Введите кол-во строк поля\n");
    if(!(scanf("%d", &str)) || !str)
        return;
    
    // Всего элементов на поле
    countEl = str*str;

    printf("Введите начальное положение\n");
    if(!(scanf("%d", &start)) || start <= 0 || start > countEl)
        return;

    printf("Введите конечное положение\n");
    if(!(scanf("%d", &finish)) || finish <= 0 || finish > countEl)
        return;
    start -= 1;
    finish -= 1;

    if(!(A = (int*)malloc(countEl * sizeof(int))))
        return;
    x = 0;
    for (i = 0; i < countEl; i++) 
        A[i] = ++x;

    step(A,str,start,finish);

    free(A);
    return;
}
