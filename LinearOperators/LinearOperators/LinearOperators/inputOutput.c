#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

double **filling_matrix(char *argv[], double **matrix) {
	int i, j, size;
	FILE *fp = NULL;

	fp = fopen(argv[1], "rt");
	if (!fp) {
		printf("File open error\n");
		return NULL;
	}

	if (!(fscanf(fp, "%d", &size))) {
		printf("Incorrect size of matrix\n");
		return 0;
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (!(fscanf(fp, "%lf", &matrix[i][j]))) {
				printf("Incorrect coefficient of matrix\n");
				return NULL;
			}
		}
	}

	return matrix;
}

int get_size(char *argv[]) {
	int size;
	FILE *fp = NULL;

	fp = fopen(argv[1], "rt");
	if (!fp) {
		printf("File open error\n");
		return 0;
	}

	if (!(fscanf(fp, "%d", &size))) {
		printf("Incorrect size of matrix\n");
		return 0;
	}

	return size;
}

double **init_matrix(double **matrix, int size) {
	int i;

	if(!(matrix = (double**)malloc(size * sizeof(double*))))
		return NULL;
	for (i = 0; i < size; i++)
		if (!(matrix[i] = (double*)malloc(size * sizeof(double))))
			return NULL;

	return matrix;
}

/* Output Matrix */
void displayMatrix(double **matrix, int size) {
	int i, j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("%4g ", matrix[i][j]);
		}
		printf("\n");
	}
}
