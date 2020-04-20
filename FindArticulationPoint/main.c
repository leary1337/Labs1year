#include <stdio.h>
#include <stdlib.h>
#include "input_output.h"
#include "articulation_point_search.h"

int main() {
	int i, j, countVertices;
	int **adjencency_Matrix;

	if(!(countVertices = get_num_vertices()))
		return 0;

	if(!(adjencency_Matrix = init_adjencency_Matrix(adjencency_Matrix, countVertices)))
		return 1;

	if(!(adjencency_Matrix = fill_adjencency_Matrix(adjencency_Matrix, countVertices))) {
		printf("Incorrect coefficient in Adjencency Matrix");
		return 0;
	}

	display_adjencency_Matrix(adjencency_Matrix, countVertices);

	prepare_for_task(adjencency_Matrix, countVertices);
	
	return 0;
}