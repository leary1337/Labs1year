#ifndef ARTICULATION_POINT_SEARCH
#define ARTICULATION_POINT_SEARCH
#define min(x, y) ( (x) < (y) ? (x) : (y) )

void prepare_for_task(int **adjencency_Matrix, int countVertices);

int do_depth_first_search(int vertex, int parent, int **adjencency_Matrix, int countVertices, int *timer_in, int visitTime);

void is_cutpoint(int vertex);

#endif // ARTICULATION_POINT_SEARCH