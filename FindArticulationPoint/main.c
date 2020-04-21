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
	int **adjencencyMatrix = 0;

	// Get the number of vertices from the user
	if(!(countVertices = get_numVertices()))
		return 0;

	// Initialize the adjacency matrix
	if(!(adjencencyMatrix = init_adjencencyMatrix(adjencencyMatrix, countVertices)))
		return 1;

	// Fill in the adjacency matrix (this is done by the user)
	if(!(adjencencyMatrix = fill_adjencencyMatrix(adjencencyMatrix, countVertices))) {
		printf("Incorrect coefficient in Adjencency Matrix");
		return 0;
	}

	// Display the resulting adjacency matrix on the screen
	display_adjencencyMatrix(adjencencyMatrix, countVertices);

	// Preparation and execution of the main task
	prepare_and_run(adjencencyMatrix, countVertices);
	
	ClearMemory(adjencencyMatrix, countVertices);
	return 0;
}
