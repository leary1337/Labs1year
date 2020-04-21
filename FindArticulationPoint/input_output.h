#ifndef INPUT_OUTPUT
#define INPUT_OUTPUT

// Initialization Adjencency Matrix (allocation memory and init with zero)
int **init_adjencencyMatrix(int **adjencencyMatrix, int countVertices);

// Filling Adjencency Matrix (user)
int **fill_adjencencyMatrix(int **adjencencyMatrix, int countVertices);

// Output Adjencency Matrix to the console
void display_adjencencyMatrix(int **adjencencyMatrix, int countVertices);

// Getting the number of vertices in the graph from the User
int get_numVertices();

// Clear Memory
void ClearMemory(void **mem, int size);

#endif // INPUT_OUTPUT
