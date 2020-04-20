/*	Task #20: 
* Найти точки сочленения связного графа. Вершина v графа G = (V, E) называется точкой
* сочленения, или разделяющей вершиной, если граф G − v содержит больше компонент
* связности, чем граф G.
*
* Author: Kalabin Danil, IVT-13BO
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "input_output.h"
#include "articulation_point_search.h"

int main() {
	int countVertices;
	int **adjencency_Matrix = 0;

	// Get the number of vertices from the user
	if(!(countVertices = get_num_vertices()))
		return 0;

	// Initialize the adjacency matrix
	if(!(adjencency_Matrix = init_adjencency_Matrix(adjencency_Matrix, countVertices)))
		return 1;

	// Fill in the adjacency matrix (this is done by the user)
	if(!(adjencency_Matrix = fill_adjencency_Matrix(adjencency_Matrix, countVertices))) {
		printf("Incorrect coefficient in Adjencency Matrix");
		return 0;
	}

	// Display the resulting adjacency matrix on the screen
	display_adjencency_Matrix(adjencency_Matrix, countVertices);

	// Preparation and execution of the main task
	prepare_for_task(adjencency_Matrix, countVertices);
	
	ClearMemory(adjencency_Matrix, countVertices);
	return 0;
}
