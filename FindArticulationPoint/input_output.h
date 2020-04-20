#ifndef INPUT_OUTPUT
#define INPUT_OUTPUT

// Initialization Adjencency Matrix (allocation memory and init with zero)
int **init_adjencency_Matrix(int **adjencency_Matrix, int countVertices);
// Filling Adjencency Matrix (user)
int **fill_adjencency_Matrix(int **adjencency_Matrix, int countVertices);
// Output Adjencency Matrix to the console
void display_adjencency_Matrix(int **adjencency_Matrix, int countVertices);
// Getting the number of vertices in the graph from the User
int get_num_vertices();
// Clear Memory
void ClearMemory(void **mem, int size);

#endif // INPUT_OUTPUT
