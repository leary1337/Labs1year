#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "articulation_point_search.h"

// Prepare and complete the task
void prepare_for_task(int **adjencency_Matrix, int countVertices) {
	int i;
	visitTime = 0;

	/*	Explanation of Variables:
	* disc, low - tags,
	* visited(bool) - mark visited peaks, ArtPoints(bool) - mark articulation points
	*/

	int *disc, *low, *parent;
	int *visited, *ArtPoints;

	disc = (int*)malloc(countVertices * sizeof(int));
	low = (int*)malloc(countVertices * sizeof(int));
	parent = (int*)malloc(countVertices * sizeof(int));
	visited = (int*)malloc(countVertices * sizeof(int));
	ArtPoints = (int*)malloc(countVertices * sizeof(int));

	// Variable initialization
	for (i = 0; i < countVertices; i++) {
		disc[i] = -1;
		low[i] = infinite;
		parent[i] = -1;
		visited[i] = 0;
		ArtPoints[i] = 0;
	}

	// Let's go do the task
	dfs_ap(adjencency_Matrix, disc, low, visited, parent, ArtPoints, 0, countVertices);
	print_art_point(ArtPoints, countVertices);
}

// Depth search and articulation point calculation
void dfs_ap(int **adjMat, int *disc, int *low, int *visited, int *parent, int *ArtPoints, int vertex, int countVertices) {
	int i;

	visited[vertex] = 1;
	visitTime = disc[vertex] = low[vertex] = visitTime + 1;
	int child = 0;
	for (i = 0; i < countVertices; i++) {
		if (adjMat[vertex][i] == 1) {
			if (visited[i] == 0) {

				child = child + 1;
				parent[i] = vertex;
				dfs_ap(adjMat, disc, low, visited, parent, ArtPoints, i, countVertices);
				low[vertex] = MIN(low[vertex], low[i]);

				// Check if the root is an Articulation point or not
				if (parent[vertex] == -1 && child > 1)
					ArtPoints[vertex] = 1;
				// Check if the other nodes are Articulation points or not
				if (parent[vertex] != -1 && low[i] >= disc[vertex] && low[i] != infinite)
					ArtPoints[vertex] = 1;
			}
			else if (parent[vertex] != i)
				low[vertex] = MIN(low[vertex], disc[i]);
		}
	}
}

// Display the result of the program
void print_art_point(int *ArtPoints, int countVertices) {
	int i;
	for(i = 0; i < countVertices; i++)
		if(ArtPoints[i])
			printf("\nArticulation Point: %c", 'A'+i);
}
