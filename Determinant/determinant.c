#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#define NOT_OK -1
#define swap(t,a,b) {t temp; temp = a; a = b; b = temp;}

// ======= ������� ��� ������� =======
int searchZeroes(int **, int );
int Rec_Laplass(int **, int );
int minorA(int **, int , int );
int sign(int j);
int Transponir(int **, int);
// ===================================

// ====== ������� ��� �������� =======
int Leibniz(long int **, int );
int NextSet(int *, int );
void swapEl(int *, int , int );
int NumInvers(int *, int );
long int factorial(long int );
// ===================================

// ======= ������� ��� ������ ========
int Gauss(long int **, int );
// ===================================

// ========== ����� ������� ==========
void displayMatrix(long int **, int );
void CheckMem(void *);
void ClearMemory(void **, int );
void AnalyzeMatrix(int **, int );
// ===================================

// ====== ���������� ���������� ======
int ind, fixsize, BadMatrix;
// ===================================

void main(int argc, char *argv[]) {
	int i, j, n;
	long int **A,det1, det2, det3;

	setlocale(LC_ALL, "rus");

	FILE *fp = NULL;

	fp = fopen("test42.txt", "rt");
	if (fp == NULL) {
		printf("\n�� ������� ������� ����\n");
		system("pause");
		return;
	}

	if (!(fscanf(fp, "%d", &n))) { // ��������� ������ 
		printf("\n����������� ������ ������ �������\n");
		system("pause");
		return;
	}

	A = (int**)malloc(n * sizeof(int*)); // ���� ������� �
	CheckMem(A);
	for (i = 0; i < n; i++) {
		A[i] = (int*)malloc(n * sizeof(int));
		CheckMem(A[i]);
		for (j = 0; j < n; j++) {
			if (!(fscanf(fp, "%d", &A[i][j]))) {
				printf("\n����������� ������� �������� �������\n");
				system("pause");
				return;
			}
		}
	}

	AnalyzeMatrix(A, n);
	displayMatrix(A, n); // ����� ������� �

	// ������:
	printf("====== ����������� ������� ������� ======\n");
	fixsize = n;
	det1 = Rec_Laplass(A, n);
	printf("������������ ������� �� ����������� ������� = %d\n", det1);
	// �������
	printf("\n====== ������������� ������� ��������: ======\n");
	printf("������������ ������� �� ������������� �������:\n");
	det2 = Leibniz(A, n);
	printf(" = %d\n", det2);
	// ����� ������
	printf("\n====== ����� ������: ======\n");
	det3 = Gauss(A, n);
	printf(" = %d\n", det3);

	system("pause");
	ClearMemory(A, n);
	fclose(fp);
	return;
}

// ========= ������ ������: =========
/* ����� ����������� ���-�� ����� � ������/������� */
int searchZeroes(int **a, int size) {
	int i, j, countRow = 0, countCol = 0, max = 0, itsRow = 0, ind = 0;

	for (i = 0; i < size; i++) {
		countCol = 0;
		countRow = 0;
		for (j = 0; j < size; j++) {
			if (a[i][j] == 0)
				countRow++;
			if (a[j][i] == 0)
				countCol++;
		}

		if (countCol > countRow) {
			if (countCol > max) {
				max = countCol;
				itsRow = 0;
				ind = i;
			}
		}
		else {
			if (countRow >= max) {
				max = countRow;
				itsRow = 1;
				ind = i;
			}
		}
	}


	if (!max) 
		itsRow = 1;

	return itsRow;
}

int Rec_Laplass(int **a, int size) {
	int j, checkOnRows, rezult = 0,dettemp = 0,mainchislo = 0,temp = 0;
	
	// ������� ������
	if (size == 1) {
		return a[0][0];
	}
	if (size == 2) {
		return a[0][0] * a[1][1] - a[0][1] * a[1][0];
	}
	if (BadMatrix)
		return 0;

	// �������� �� ��, �� ��� ����� ������������ (������ ��� �������)
	checkOnRows = searchZeroes(a, size); 

	// ���� ����� ������������� �� �������, �� ������������� ���� ������� (������������ �� ���������)
	if (checkOnRows != 1) {
		a = Transponir(a, size);
	}
	if (fixsize == size) 
		printf("���������� ������������ �� %d ������:\n", ind+1);

	// ���������� �� ������
	for (j = 0; j < size; j++) {

		// ���� ������� ����� ����, �� ���������� ���
		if (a[ind][j] == 0)
			continue;
		
		// ���� ����
		mainchislo = sign(j)*a[ind][j];
		if (fixsize == size)
			printf("%d\n", mainchislo);

		dettemp = Rec_Laplass(minorA(a, size, j), size - 1);
		temp = mainchislo * dettemp;
		if (fixsize == size) 
			printf("= %d*(%d) = %d\n", mainchislo, dettemp, temp);
		
		rezult += temp;
	}
	return rezult;
}

int minorA(int **a, int size, int col) {
	int **B, i, j, i1, j1;

	B = (int**)malloc((size-1) * sizeof(int*));
	CheckMem(B);
	for (i = 0; i < size; i++) {
		B[i] = (int)malloc((size - 1) * sizeof(int));
		CheckMem(B[i]);
	}

	for (i = 0, i1 = 0; i < size; i++, i1++) {
		for (j = 0, j1 = 0; j < size; j++, j1++) {
			if (i == ind) {
				i1--;
				break;
			}
			if (j == col) {
				j1--;
				continue;
			}

			B[i1][j1] = a[i][j];
		}
	}
	if (fixsize == size)
		displayMatrix(B, size - 1);
	return B;
}

int sign(int j) {
	if ((ind + j) % 2 == 0)
		return 1;
	else
		return -1;
}
/* ���������������� ������� */
int Transponir(int **A, int size) {
	int i, j, **B;

	B = (int**)malloc(size * sizeof(int*));
	CheckMem(B);
	for (i = 0; i < size; i++) {
		B[i] = (int)malloc(size * sizeof(int));
		CheckMem(B[i]);
		for (j = 0; j < size; j++)
			B[i][j] = A[j][i];
	}
	return B;
}
// ===================================

// ========= ������� ������: =========
int Leibniz(long int **arr, int size) {
	int i, j, slag, col, *arr_perms = NULL, rezult = 0;
	long int factor = 0;
	if (BadMatrix)
		return 0;
	// ���-�� ���������
	factor = factorial(size);
	// ������ ��� ������������ � ��� �������������
	arr_perms = (int*)malloc(size * sizeof(int));
	CheckMem(arr_perms);
	for (i = 0; i < size; i++)
		arr_perms[i] = i;
	if (size > 4)
		printf("��������� ���������, ������ ������ ���������\n");
	// ������������ ���������� (���� ����)
	for (i = 0; i < factor; i++) {
		slag = 1;
		if (size < 5) {
			if (NumInvers(arr_perms, size) == 1) {
				if (i != 0) {
					printf(" + ");
				}
			}
			else
				printf(" - ");
		}
		for (j = 0; j < size; j++) {
			col = arr_perms[j];
			slag *= arr[j][col];
			if (size < 5) {
				if (j == size-1) 
					printf("%d", arr[j][col]);
				else 
					printf("%d*", arr[j][col]);
			}
		}
		rezult += NumInvers(arr_perms, size) * slag;
		NextSet(arr_perms, size);
	}

	free(arr_perms);

	return rezult;
}
/* ��������� ������������ */
int NextSet(int *per, int size) {
	int j = size - 2;
	while (j != -1 && per[j] >= per[j + 1]) 
		j--;
	if (j == -1)
		return 0; // ������ ������������ ���
	int k = size - 1;
	while (per[j] >= per[k]) 
		k--;
	swapEl(per, j, k);
	int l = j + 1, r = size - 1; // ��������� ���������� ����� ������������������
	while (l < r)
		swapEl(per, l++, r--);
	return 1;
}
/* ��� ����������� ������� */
void swapEl(int *per, int i, int j) {
	int tmp = per[i];
	per[i] = per[j];
	per[j] = tmp;
}
/* ����� �������� � ������������ (�� � ����� � ����� ���� ����� ����� ���������) */
int NumInvers(int *per, int size) {
	int i, j, tmp, count = 0;
	for (i = 0; i < size; i++) {
		tmp = per[i];
		for (j = i+1; j < size; j++) {
			if (tmp > per[j])
				count++;
		}
	}
	// ���������� ����
	if (count % 2 == 0)
		return 1;
	else
		return -1;
}
/* ��������� ��������� */
long int factorial(long int a) {
	if (a > 10)
		return NOT_OK;
	if (a == 0 || a == 1) return 1;
	return a * factorial(a - 1);
}
// ===================================

// ========== ����� ������: ==========
int Gauss(long int **c, int n) {
	int i, j, k, indMin, ColSwaps = 1, q,qM;
	long double determ = 1;
	long int koef = 1;

	if (BadMatrix)
		return 0;

	for (i = 0; i < n; i++) {
		if (i == 0)
			displayMatrix(c, n);
		indMin = i;
		// ���� ������ � ������ ����������� ���������
		for (j = i + 1; j < n; j++)
			if (abs(c[j][i]) < abs(c[indMin][i]))
				if (c[j][i] < 0)
					indMin = j;
		for (k = 0; k < n; k++)
			swap(int, c[i][k], c[indMin][k]);
		ColSwaps = -ColSwaps * (i != indMin ? 1 : -1);

		for (j = i; j < n; j++) {
			if (n > j+1) {
				// ��������� �� ������� �������, ����� ��� �����
				if (!c[i][i])
					break;
				if (c[j+1][i] % c[i][i] != 0) {
					for (k = i; k < n; k++)
						c[j+1][k] *= c[i][i];
					koef *= c[i][i];
					printf("\n������������ � ����� ��������� �� (1/%li)\n", koef);
					displayMatrix(c, n);
				}
				
				// �������� ������ �� ���� ���������
				q = c[j+1][i] / c[i][i];
				
				for (k = 0; k < n; k++) {
					if (q >= 0)
						c[j+1][k] -= q * c[i][k];
					else
						c[j+1][k] += -q * c[i][k];
				}
				if (q >= 0)
					printf("\n(%d) - %d*(%d)\n", j + 2, q, i + 1);
				else
					printf("\n(%d)%d*(%d)\n", j + 2, q, i + 1);
				displayMatrix(c, n);
			}
		}
	}
	if (koef == 0)
		return 0;
	printf("������������ ������� �� ������ ������: ");
	for (i = 0; i < n; i++) {
		if (i == 0) {
			if (koef != 1)
			 printf("(1/%li)*", koef);
			if (c[i][i] < 0)
				printf("(%d)", c[i][i]);
			else
				printf("%d", c[i][i]);
		}
		else
			if (c[i][i] < 0)
				printf("*(%d)", c[i][i]);
			else
				printf("*%d", c[i][i]);
		determ *= c[i][i];
	}
	if (koef != 1)
		determ /= koef;
	return determ*ColSwaps;
}
// ===================================

// ========= ����� ������� ===========
/* ����� ������� */
void displayMatrix(long int **A, int size) {
	int i, j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("%4d ", A[i][j]);
		}
		printf("\n");
	}
}
/* �������� ��������� ������ */
void CheckMem(void *mem) {
	if (mem == NULL) {
		printf("\n�� ������� �������� ������!\n");
		exit(0);
	}
}
/* ������� ������ */
void ClearMemory(void **mem, int size) {
	int i;
	for (i = 0; i < size; i++) {
		free(mem[i]);
	}
	free(mem);
}
/* �������� �� ��, ��� ������� �������� */
void AnalyzeMatrix(int **A, int size) {
	int i, j, k, count = 0, el;
	el = A[0][0];
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
			if (A[i][j] == el)
				count++;
	}
	if (count == (size*size))
		BadMatrix = 1;
	else
		BadMatrix = 0;
}
// ===================================