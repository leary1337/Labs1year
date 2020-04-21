#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Initialization Adjencency Matrix (allocation memory and init with zero)
int **init_adjencencyMatrix(int **adjencencyMatrix, int countVertices) {
	int i, j;

	// Allocation memory for Adjencency Matrix and initialization Matrix with zero
	if(!(adjencencyMatrix = (int**)malloc(countVertices * sizeof(int*))))
		return NULL;
	for(i = 0; i < countVertices; i++) { 
		if(!(adjencencyMatrix[i] = (int*)malloc(countVertices * sizeof(int))))
			return NULL;

		for(j = 0; j < countVertices; j++)
			adjencencyMatrix[i][j] = 0;
	}

	return adjencencyMatrix;
}

// Filling Adjencency Matrix (user)
int **fill_adjencencyMatrix(int **adjencencyMatrix, int countVertices) {
	int i, j, tmp;

	printf("Fill in the adjacency matrix:\n");
	for(i = 0; i < countVertices; i++) {
		for(j = 0; j < countVertices; j++) {
			// Filling the upper trugular matrix
			if(i > j || i == j) continue; 

			printf("%c -> %c: ", 'A' + i, 'A' + j);

			if(!scanf("%d", &tmp) && tmp < 0) 
				return NULL;
			adjencencyMatrix[i][j] = adjencencyMatrix[j][i] = tmp;
		}
	}

	return adjencencyMatrix;
}

// Output Adjencency Matrix to the console
void display_adjencencyMatrix(int **adjencencyMatrix, int countVertices) {
	int i, j;

	printf("\n\nAdjacency Matrix:\n  ");
	for (i = 0; i < countVertices; i++)
		printf("%c ", 'A' + i);

	for (i = 0; i < countVertices; i++) {
		printf("\n%c ", 'A' + i);
		for (j = 0; j < countVertices; j++) {
			printf("%d ", adjencencyMatrix[i][j]);
		}
	}
	printf("\n");
}

// Getting the number of vertices in the graph from the User
int get_numVertices() {
	int countVertices;

	printf("Input number of Vertices: ");
	if(!scanf("%d", &countVertices) || countVertices < 0) {
		printf("Incorrect number of Vertices");
		return 0;
	}

	return countVertices;
}

// Clear Memory
void ClearMemory(void **mem, int size) {
	int i;
	for (i = 0; i < size; i++) {
		free(mem[i]);
	}
	free(mem);
}
