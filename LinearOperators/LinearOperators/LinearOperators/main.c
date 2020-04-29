#include <stdio.h>
#include "inputOutput.h"

int main(int argc, char *argv[]) {
	int i, j, size;
	double **matrix = NULL;
	
	if (!(size = get_size(argv)))
		return 0;

	if (!(matrix = init_matrix(matrix, size))) {
		printf("Memory isn't allocated\n");
		return 1;
	}

	if (!(matrix = filling_matrix(argv, matrix)))
		return 0;

	displayMatrix(matrix, size);

	return 0;
}