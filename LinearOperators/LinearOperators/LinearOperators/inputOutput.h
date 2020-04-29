#ifndef INPUT_OUTPUT
#define INPUT_OUTPUT

double **filling_matrix(char *argv[], double **matrix);

double **init_matrix(double **matrix, int size);

void displayMatrix(double **matrix, int size);

int get_size(char *argv[]);

#endif // INPUT_OUTPUT