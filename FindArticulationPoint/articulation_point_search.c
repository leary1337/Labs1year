#include <stdio.h>
#include <stdlib.h>
#include "articulation_point_search.h"

void prepare_for_task(int **adjencency_Matrix, int countVertices) {
	int i;
	// "timer" for determining the times
	int visitTime = 0;
	// tin[i] - time to go deep into vertex i, 
	// low[i] - minimum from the time of entry to the very peak tin[i]
	int *time_in; 

	if(!(time_in = (int*)malloc(countVertices * sizeof(int))))
		return;

	// Let's go do the task
	do_depth_first_search(0, -1, adjencency_Matrix, countVertices, time_in, visitTime);
}

// Depth-first search in graph
int do_depth_first_search(int vertex, int parent, int **adjencency_Matrix, int countVertices, int *time_in, int visitTime) {
	int i, min_time, x, y, tmp;

	time_in[vertex] = ++visitTime;
	min_time = time_in[vertex];
	x = 0;
	y = (parent != -1);
	printf("STEP");

	for(i = 0; i < countVertices; i++) {
		if(adjencency_Matrix[vertex][i]) {
			if(!time_in[i]) { // Not visited yet
				tmp = do_depth_first_search(i, vertex, adjencency_Matrix, countVertices, time_in, visitTime);
				if(tmp >= time_in[vertex])
					++x;
			}
			else 
				tmp = time_in[i];
			min_time = min(min_time, tmp);	
		}
	}
	if(x + y >= 2)
		printf("IS_CUTPOINT");

	return min_time;
}

void is_cutpoint(int vertex) {
	printf("%c", 'A'+vertex);
}