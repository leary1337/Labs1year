#ifndef ARTICULATION_POINT_SEARCH
#define ARTICULATION_POINT_SEARCH
#define MIN(x, y) ( (x) < (y) ? (x) : (y) )

// Make this bigger as possible if you work for graphs that have more than 1000000000 node
// TODO change according to the maximum number of nodes
#define infinite 1000000000

// Entry time
int visitTime;

// Prepare and complete the task
void prepare_for_task(int **adjencency_Matrix, int countVertices);

// Depth search and articulation point calculation
	/*	Explanation of Variables:
	* adj - Adjencency Matrix,
	* disc, low - tags,
	* visited(bool) - mark visited peaks, ArtPoints(bool) - mark articulation points
	*/
void dfs_ap(int **adj, int *disc, int *low, int *visited, int *parent, int *ArtPoints, int vertex, int countVertices);

// Display the result of the program
void print_art_point(int *ArtPoints, int countVertices);

#endif // ARTICULATION_POINT_SEARCH
