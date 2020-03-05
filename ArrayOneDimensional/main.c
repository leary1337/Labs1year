/*
    Задание 1.3. Нестандартное применение одномерных массивов
    Король, №2, поле №8
*/
#include <stdio.h>
#include <stdlib.h>

// Ищет в какой строке указанный элемент
int searchStrEl(int *A,int strs, int elem) {
    int i, str, indR, indL;

    for(i = 0; i <= strs; i++) {
        indR = i*i-1;
        indL = (i-1)*(i-1);
        
        if(elem >= indL && elem <= indR) {
            str = i;
        }
    }

    return str;
}

void step(int *A, int n, int a, int b) {
    int strB, currStr;

    printf("%d ", a);
    strB = searchStrEl(A, n, b);

    currStr = searchStrEl(A, n, a);
    if(currStr == strB) {
        if(a == b)
            return;

        if(a < b)
            step(A,n,++a,b);

        if(a > b)
            step(A,n,--a,b);
    }
    if(currStr < strB) {
        a += currStr*2;
        currStr++;
        step(A,n,a,b);
    }
    if(currStr > strB) {
        currStr--;
        a -= currStr*2;
        step(A,n,a,b);
    }
}


void main() {
    int i,a, b, n, x, countEl, *A, *B, *C;

    printf("Введите кол-во строк поля\n");
    if(!(scanf("%d", &n)))
        return;

    printf("Введите начальное положение\n");
    if(!(scanf("%d", &a)))
        return;

    printf("Введите конченое положение\n");
    if(!(scanf("%d", &b)))
        return;
    b -= 1;
    a -= 1;

    countEl = n*n;

    if(!(A = (int*)malloc(countEl * sizeof(int))))
        return;

    

    printf("Всего элементов: %d\n", countEl);
    x = 0;
    for (i = 0; i < countEl; i++) 
        A[i] = ++x;

    step(A,n,a,b);

/*
    // Нашли строку в которой указанный начальный элемент и крайние элементы в этой строке
    for(i = 0; i <= n; i++) {
        indRa = i*i-1;
        indLa = (i-1)*(i-1);
        
        if(a >= indLa && a <= indRa) {
            strA = i;
            printf("Начальное в %d строке\n", strA);
        }
    }

    // Нашли строку в которой указанный конечный элемент и крайние элементы в этой строке
    for(i = 0; i <= n; i++) {
        indRb = i*i-1;
        indLb = (i-1)*(i-1);
        
        if(b >= indLb && b <= indRb) {
            strB = i;
            printf("Конечная в %d строке\n", strB);
        }
    }

    if (a == b) {
        printf("Вы дебилы!");
        return;
    }

    if(strA == strB) {
        if(a < b)
            for(i = a; i <= b; i++) 
                printf("%d ", i);        
        if(a > b)
           for(i = a; i >= b; i--) 
                printf("%d ", i);  
        
    }
    
    if(strA < strB) {
        curr = a;
        for(i = strA; i < strB; i++) {
            printf("%d ", curr);
            curr += i*2;
        }
        
        if(curr < b)
            for(i = curr; i <= b; i++) 
                printf("%d ", i);    

        if(curr > b)
           for(i = curr; i >= b; i--) 
                printf("%d ", i); 

        if (curr == b)
            printf("%d ", curr);

    }

    if(strA > strB) {
        curr = a;
        for(i = strA; i < strB; i--) {
            printf("%d ", curr);
            curr -= (i-1)*2;
        }
        
        if(curr < b)
            for(i = curr; i <= b; i++) 
                printf("%d ", i);    

        if(curr > b)
           for(i = curr; i >= b; i--) 
                printf("%d ", i); 

        if (curr == b)
            printf("%d ", curr);
    }
*/
/*
    for(i = n; i > 0; i--) {
        indR = (i-1)*(i-1)-1;
        indL = indR + 1;
        printf("%d ", indL);
        indD = indL;
        for(j = i; j < n; j++) {
            indD += j*2;
            printf("%d ", indD);
        }
    }
    for(i = 2; i <= n; i++) {
        indR = i*i-1;
        indD = indR;
        printf("%d ", indR);
        for(j = i; j < n; j++) {
            indD += j*2;
            printf("%d ", indD); 
        }
    }
*/

    return;
}
