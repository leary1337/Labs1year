#ifndef ARTICULATION_POINT_SEARCH
#define ARTICULATION_POINT_SEARCH
#define MIN(x, y) ( (x) < (y) ? (x) : (y) )

// Make this bigger as possible if you work for graphs that have more than 1000000000 node
// TODO change according to the maximum number of nodes
#define INF 1000000000

// Entry time
int visitTime;

// Prepare and complete the task
void prepare_and_run(int **adjencencyMatrix, int countVertices);

// Depth search and articulation point calculation
	/*	Explanation of Variables:
	* adj - Adjencency Matrix,
	* disc, low - tags,
	* visited(bool) - mark visited peaks, artPoints(bool) - mark articulation points
	*/
void dfs_ap(int **adj, int *disc, int *low, int *visited, int *parent, int *artPoints, int vertex, int countVertices);

// Display the result of the program
void print_ap(int *artPoints, int countVertices);

// Clear memory
void clear_all(int *disc, int* low, int *visited, int *parent, int *artPoints);

#endif // ARTICULATION_POINT_SEARCH
