#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Initialization Adjencency Matrix (allocation memory and init with zero)
int **init_adjencency_Matrix(int **adjencency_Matrix, int countVertices) {
	int i, j;

	// Allocation memory for Adjencency Matrix and initialization Matrix with zero
	if(!(adjencency_Matrix = (int**)malloc(countVertices * sizeof(int*))))
		return NULL;
	for(i = 0; i < countVertices; i++) { 
		if(!(adjencency_Matrix[i] = (int*)malloc(countVertices * sizeof(int))))
			return NULL;

		for(j = 0; j < countVertices; j++)
			adjencency_Matrix[i][j] = 0;
	}

	return adjencency_Matrix;
}

// Filling Adjencency Matrix (user)
int **fill_adjencency_Matrix(int **adjencency_Matrix, int countVertices) {
	int i, j, tmp;

	printf("Fill in the adjacency matrix:\n");
	for(i = 0; i < countVertices; i++) {
		for(j = 0; j < countVertices; j++) {
			// Filling the upper trugular matrix
			if(i > j || i == j) continue; 

			printf("%c -> %c: ", 'A' + i, 'A' + j);

			if(!scanf("%d", &tmp) && tmp < 0) 
				return NULL;
			adjencency_Matrix[i][j] = adjencency_Matrix[j][i] = tmp;
		}
	}

	return adjencency_Matrix;
}

// Output Adjencency Matrix to the console
void display_adjencency_Matrix(int **adjencency_Matrix, int countVertices) {
	int i, j;

	printf("\n\nAdjacency Matrix:\n  ");
	for (i = 0; i < countVertices; i++)
		printf("%c ", 'A' + i);

	for (i = 0; i < countVertices; i++) {
		printf("\n%c ", 'A' + i);
		for (j = 0; j < countVertices; j++) {
			printf("%d ", adjencency_Matrix[i][j]);
		}
	}
	printf("\n");
}

// Getting the number of vertices in the graph from the User
int get_num_vertices() {
	int countVertices;

	printf("Input number of Vertices: ");
	if(!scanf("%d", &countVertices) || countVertices < 0) {
		printf("Incorrect number of Vertices");
		return 0;
	}

	return countVertices;
}
