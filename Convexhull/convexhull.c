#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define swap(t,a,b) {t temp; temp = a; a = b; b = temp;}
#define N 3
#define EPS 0.000001


/* Convex Hull (A) Functions */
double *check_potential_faces(double **);
double determinate_rate_ineq(double*);
int check_linear_dep(double **, double*);
int NOD(int , int);

/* Vertex Enumeration (B1) Functions */
double *vertex_enumeration(double **);
int Calc_Point(double* , double* , double*);
int check_ident_point(double **);
int check_potential_vertices(double **);
int cramer(double[N][N], double[N]);
double det(double[N][N]);

/* Skeleton's (B2) Functions */
int skeleton(double **, double **, int );
int create_graph(double **, double **, int **);
void displayInfoFace(int *, int );
void displayAdjacencyMatrix(int **);

/* Utilities Functions */
void print_points(double **);
void print_ineq(double**, int, int);
void MemCheck(void*);
void ClearMemory(void**, int);

/* Global vars */
int countIneq = 0, countPoints = 0;
double *tmpPoint;
double x[N];

int main(int argc, char* argv[]) {
	int i, j, size;
	char modeWork;

	// Point designation
	double **setPoints;
	// Inequality designation
	double **arrIneq;

	FILE* fp = NULL;

	if (argc == 2) {
		fp = fopen(argv[1], "rt");
		if (fp == NULL) {
			printf("\nCould not open file.\n");
			return 1;
		}

		if (!(fscanf(fp, "%c", &modeWork))) {
			printf("\nIncorrect work type\n");
			return 1;
		}

		if (!(fscanf(fp, "%d", &size))) {
			printf("\nIncorrect number of dots\n");
			return 1;
		}

		switch (modeWork) {
			// Vertex
		case 'V':
			printf("\nSelected type V\n");

			countPoints = size;

			// Память под координаты точек
			setPoints = (double**)malloc(countPoints * sizeof(double*));
			MemCheck(setPoints);
			for (i = 0; i < countPoints; i++) {
				setPoints[i] = (double*)malloc(countPoints * sizeof(double));
				MemCheck(setPoints[i]);
			}

			printf("Number of Points: %d\n", countPoints);

			// Input and Output Dots
			for (i = 0; i < countPoints; i++) {
				for (j = 0; j < 3; j++) {
					if (!(fscanf(fp, "%lf", &setPoints[i][j]))) {
						printf("\nIncorrect coordinate\n");
						return 1;
					}
				}
			}
			print_points(setPoints);
			arrIneq = check_potential_faces(setPoints);
			printf("Number of Faces: %d\n", countIneq);
			print_ineq(arrIneq, 0, countIneq);

			//ClearMemory(setPoints, countPoints);
			//ClearMemory(arrIneq, (countPoints * 7));
			//countPoints = 0;
			//countIneq = 0;
			break;

			// Hyperplane
		case 'H':
			printf("\nSelected type H\n");

			countIneq = size;

			// Память под неравенства
			arrIneq = (double**)malloc(countIneq * sizeof(double*));
			MemCheck(arrIneq);
			for (i = 0; i < countIneq; i++) {
				arrIneq[i] = (double*)malloc(4 * sizeof(double));
				MemCheck(arrIneq[i]);
			}

			for (i = 0; i < size; i++) {
				for (j = 0; j < 4; j++) {
					if (!(fscanf(fp, "%lf", &arrIneq[i][j]))) {
						printf("\nIncorrect coefficient\n");
						return 1;
					}
				}
				arrIneq[i][3] *= -1; // Переносим в левую часть заранее
			}
			printf("Number of Faces: %d\n", countIneq);
			print_ineq(arrIneq, 0, countIneq);

			setPoints = vertex_enumeration(arrIneq);

			printf("Number of Verctices: %d\n", countPoints);
			print_points(setPoints);

			//ClearMemory(setPoints, (countIneq * 7));
			//ClearMemory(arrIneq, countIneq);
			//countIneq = 0;
			//countPoints = 0;
			break;

		default:
			printf("\nType not selected or invalid type\n");
			return 1;
		}
		skeleton(arrIneq, setPoints, countPoints);
	}

	
	if (fclose(fp))
		printf("File close Error!\n");

	return 0;
}

/* Convex Hull (A) Functions */
double *check_potential_faces(double **setPoints) {
	int i, j, k, p, q;
	int halfspace, oops, sign;
	double tmp[4] = { 0 };
	double vectA[3], vectB[3], normVect[3], freeCoeff, check, rate;
	double **arrIneq;

	// Система неравенств (Не знаю сколько памяти нужно!)
	arrIneq = (double**)malloc((countPoints * 7) * sizeof(double*));
	MemCheck(arrIneq);
	for (i = 0; i < (countPoints * 7); i++) {
		arrIneq[i] = (double*)malloc(4 * sizeof(double));
		MemCheck(arrIneq[i]);
	}

	sign = 1;
	halfspace = 0;

	for (i = 0; i < countPoints; i++) {
		for (j = 0; j < countPoints; j++) {
			if (j == i) continue;
			vectA[0] = setPoints[j][0] - setPoints[i][0];
			vectA[1] = setPoints[j][1] - setPoints[i][1];
			vectA[2] = setPoints[j][2] - setPoints[i][2];

			for (k = 0; k < countPoints; k++) {
				if (k == j || k == i) continue;
				vectB[0] = setPoints[k][0] - setPoints[i][0];
				vectB[1] = setPoints[k][1] - setPoints[i][1];
				vectB[2] = setPoints[k][2] - setPoints[i][2];
				/*
							   | x   y   z |
				vectA x vectB: |vA1 vA2 vA3| = ax+by+cz
							   |vB1 vB2 vB3|
				*/
				normVect[0] = vectA[1] * vectB[2] - vectA[2] * vectB[1];
				normVect[1] = vectA[2] * vectB[0] - vectA[0] * vectB[2]; // Если посмотреть на определитель
				normVect[2] = vectA[0] * vectB[1] - vectA[1] * vectB[0];
				freeCoeff = normVect[0] * -setPoints[i][0] + normVect[1] * -setPoints[i][1] + normVect[2] * -setPoints[i][2];

				// Смотрим на оставшиеся точки
				halfspace = 0;
				oops = 0;
				for (p = 0; p < countPoints; p++) {
					if (p == k || p == i || p == j) continue;
					// Подставим точку в наше уравнение плоскости
					check = normVect[0] * setPoints[p][0] + normVect[1] * setPoints[p][1] + normVect[2] * setPoints[p][2] + freeCoeff;

					// Проверяем в каком полупространстве лежат оставшиеся точки
					if ((halfspace == 1 && check < 0) || (halfspace == -1 && check > 0)) {
						oops = 1;
						break;
					}
					if (check > 0)
						halfspace = 1;
					if (check < 0)
						halfspace = -1;
				}
				if (!oops) {
					if (halfspace > 0)
						sign = -1;
					else
						if (halfspace < 0)
							sign = 1;
					tmp[0] = sign * normVect[0];
					tmp[1] = sign * normVect[1];
					tmp[2] = sign * normVect[2];
					tmp[3] = sign * freeCoeff;
				}

				if (!(check_linear_dep(arrIneq, tmp)) && (!oops)) {

					rate = determinate_rate_ineq(tmp);
					if (rate != 0)
						for (q = 0; q < 4; q++)
							tmp[q] /= rate;

					arrIneq[countIneq][0] = tmp[0];
					arrIneq[countIneq][1] = tmp[1];
					arrIneq[countIneq][2] = tmp[2];
					arrIneq[countIneq][3] = tmp[3];
					countIneq++;
				}

			}
		}
	}

	return arrIneq;
}
double determinate_rate_ineq(double* tmp) {
	double rate;

	rate = NOD(NOD(fabs(tmp[0]), fabs(tmp[1])), NOD(fabs(tmp[2]), fabs(tmp[3])));
	return rate;
}
int check_linear_dep(double **arrIneq, double* tmp) {
	int i, j, count1;
	double rate;

	rate = determinate_rate_ineq(tmp);

	if (!rate)
		return 1;

	for (i = 0; i < countIneq; i++) {
		count1 = 0;
		for (j = 0; j < 4; j++) {
			if ((tmp[j] / rate) == arrIneq[i][j])
				count1++;
		}
		if (count1 == 4)
			return 1;
	}

	return 0;
}
int NOD(int a, int b) {
	if (a == 0 || b == 0)
		return a + b;
	if (a > b)
		return NOD(a - b, b);
	else
		return NOD(a, b - a);
}

/* Vertex Enumeration (B1) Functions */
double *vertex_enumeration(double **arrIneq) {
	int i, j, p, q;
	double **setPoints, check;

	// Память под координаты точек (Не знаю сколько памяти нужно!)
	setPoints = (double**)malloc((countIneq*7) * sizeof(double*));
	MemCheck(setPoints);
	for (i = 0; i < (countIneq * 7); i++) {
		setPoints[i] = (double*)malloc(3 * sizeof(double));
		MemCheck(setPoints[i]);
	}

	// Память под временный массив точки
	tmpPoint = (double*)malloc(3 * sizeof(double));
	MemCheck(tmpPoint);

	for (i = 0; i < countIneq; i++) {
		for (j = 0; j < countIneq; j++) {
			if (j <= i) continue;
			for (p = 0; p < countIneq; p++) {
				if (p <= j || p <= i) continue;
				if (check = Calc_Point(arrIneq[i], arrIneq[j], arrIneq[p]))
					continue;
				else {
					if (!check_ident_point(setPoints)) {
						if(!check_potential_vertices(arrIneq)) {
							for (q = 0; q < 3; q++)
								setPoints[countPoints][q] = tmpPoint[q];
							countPoints++;
						}
					}
				}
			}
		}
	}
	return setPoints;
}
int Calc_Point(double* ineq1, double* ineq2, double* ineq3) {
	int i, j;
	double arrayTemp[N][N], b[N];

	for (j = 0; j < 3; j++) {
		arrayTemp[0][j] = ineq1[j];
		arrayTemp[1][j] = ineq2[j];
		arrayTemp[2][j] = ineq3[j];
	}
	b[0] = -ineq1[3];
	b[1] = -ineq2[3];
	b[2] = -ineq3[3];

	if (cramer(arrayTemp, b)) {
		return 1;
	}
	else {
		for (i = 0; i < 3; i++) 
			tmpPoint[i] = x[i];

	}

	return 0;
}
int cramer(double a[N][N], double b[N]) {
	int i, j, p;
	double detA;
	double tmp[N][N];


	detA = det(a);

	if (detA == 0)
		return 1;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) 
			for (p = 0; p < N; p++) 
				tmp[j][p] = a[j][p];

		for (p = 0; p < N; p++)
			tmp[p][i] = b[p];

		x[i] = det(tmp) / detA;
	}

	return 0;
}
double det(double A[N][N]) {
	
	return	A[0][0] * A[1][1] * A[2][2] +
			A[0][1] * A[1][2] * A[2][0] +
			A[1][0] * A[2][1] * A[0][2] -
			A[2][0] * A[1][1] * A[0][2] -
			A[1][0] * A[0][1] * A[2][2] -
			A[2][1] * A[1][2] * A[0][0];
}
int check_ident_point(double **setPoints) {
	int i, j, check;

	for (i = 0; i < countPoints; i++) {
		check = 0;
		for (j = 0; j < 3; j++)
			if (setPoints[i][j] == tmpPoint[j])
				check++;
		if (check == 3)
			return 1;
	}

	return 0;
}
int check_potential_vertices(double **arrIneq) {
	int i, j;
	double res;

	for(i = 0; i < countIneq; i++) {
		res = 0;
		for(j = 0; j < 3; j++) {
			res += arrIneq[i][j] * tmpPoint[j];
		}
		if(res > (-arrIneq[i][3]))
			return 1;
	}

	return 0;
}

/* Skeleton's (B2) Functions */
int skeleton(double **arrIneq, double **setPoints, int countPoints) {
	int i, j;
	int **adjMatrix;

	// Память под Матрицу Смежности
	adjMatrix = (int**)malloc(countPoints * sizeof(int*));
	MemCheck(adjMatrix);
	for (i = 0; i < countPoints; i++) {
		adjMatrix[i] = (int*)malloc(countPoints * sizeof(int));
		MemCheck(adjMatrix[i]);
	}

	for (i = 0; i < countPoints; i++)
		for (j = 0; j < countPoints; j++)
			adjMatrix[i][j] = 0;

	create_graph(arrIneq, setPoints, adjMatrix);

	return 0;
}
int create_graph(double **arrIneq, double **setPoints, int **adjMatrix) {
	int i, j, k, p, countEdges, vert1, vert2;
	int *arrayEdge;
	double check1, check2;

	// Память под массив ребер (с запасиком)
	arrayEdge = (int*)malloc((countPoints*4) * sizeof(int));

	printf("\n*Information about Faces*");
	for (i = 0; i < countIneq; i++) {
		printf("\nFace: ");
		print_ineq(arrIneq, i, i + 1);
		countEdges = 0;
		for (j = 0; j < countIneq; j++) {
			if (i == j) continue;
			for (k = 0; k < countPoints; k++) {
				check1 = check2 = 0;

				for (p = 0; p < 3; p++) {
					check1 += arrIneq[i][p] * setPoints[k][p];
					check2 += arrIneq[j][p] * setPoints[k][p];
				}
				check1 += arrIneq[i][p];
				check2 += arrIneq[j][p];

				if (!check1 && !check2) {
					arrayEdge[countEdges] = k;
					countEdges++;
				}
			}
			if (!(countEdges % 2) && countEdges) {
				vert1 = arrayEdge[countEdges - 2];
				vert2 = arrayEdge[countEdges - 1];
				adjMatrix[vert1][vert2] = 1;
				adjMatrix[vert2][vert1] = 1;
			}
			else if (countEdges) {
				countEdges--;
				arrayEdge[countEdges] = -1;
			}
		}
		displayInfoFace(arrayEdge, countEdges);
		for (j = 0; j < (countPoints * 4); j++)
			arrayEdge[j] = -1;
	}

	displayAdjacencyMatrix(adjMatrix);

	return 0;
}
void displayAdjacencyMatrix(int **adjMatrix) {
	int i, j;

	printf("\n\nAdjacency Matrix:\n  ");
	for (i = 0; i < countPoints; i++) 
		printf("%c ", 'A' + i);
	for (i = 0; i < countPoints; i++) {
		printf("\n%c ", 'A' + i);
		for (j = 0; j < countPoints; j++) {
			printf("%d ", adjMatrix[i][j]);
		}
	}
	printf("\n");
}
void displayInfoFace(int *arrayEdge, int countEdges) {
	int i, j;

	printf("Edges: ");
	for (i = 0; i < countEdges; i++) {
		if (i % 2 == 0) {
			if (arrayEdge[i] != -1 && arrayEdge[i + 1] != -1)
				printf("%c%c ", 'A' + arrayEdge[i], 'A' + arrayEdge[i + 1]);
			for (j = i + 1; j < countEdges; j++) {
				if (arrayEdge[j] == arrayEdge[i] && arrayEdge[j + 1] == arrayEdge[i + 1])
					arrayEdge[j] = -1;
			}
		}
	}

	printf("\nVertices: ");
	for (i = 0; i < countEdges; i++) {
		if (arrayEdge[i] != -1)
			printf("%c ", 'A' + arrayEdge[i]);
		for (j = i + 1; j < countEdges; j++) {
			if (arrayEdge[j] == arrayEdge[i]) {
				arrayEdge[j] = -1;
			}
		}
	}
	printf("\n");
}

/* Utilities Functions */
void print_ineq(double** Ineq, int start, int count) {
	int i, j;
	char ch[] = { 'x', 'y', 'z', '\0' };

	for (i = start; i < count; i++) {
		for (j = 0; j < 3; j++) {
			if (Ineq[i][j] != 0) {
				if (Ineq[i][j] == 1 && j != 0)
					printf("+%c", ch[j]);

				if (Ineq[i][j] == 1 && j == 0)
					printf("%c", ch[j]);

				if (Ineq[i][j] == -1)
					printf("-%c", ch[j]);

				if (Ineq[i][j] > 1 && j != 0)
					printf("+%g%c", (fabs(Ineq[i][j]) < EPS) ? 0.0 : Ineq[i][j], ch[j]);

				if (Ineq[i][j] > 1 && j == 0)
					printf("%g%c", (fabs(Ineq[i][j]) < EPS) ? 0.0 : Ineq[i][j], ch[j]);

				if (Ineq[i][j] < -1)
					printf("%g%c", (fabs(Ineq[i][j]) < EPS) ? 0.0 : Ineq[i][j], ch[j]);
			}
		}
		// Минус так как переносим в правую часть неравенства
		printf("<=%g\n", (fabs(Ineq[i][j]) < EPS) ? 0.0 : -Ineq[i][3]);
	}
}
void print_points(double **setPoints) {
	int i, j, num;
	char ch = 65;

	for (i = 0; i < countPoints; i++) {
		printf("%c: ", ch++);
		for (j = 0; j < 3; j++) {
			// Чтобы не выводило отрицательный нуль
			printf("%2g ", (fabs(setPoints[i][j]) < EPS) ? 0.0 : setPoints[i][j]);
		}
		printf("\n");
	}
	if (i > 26 && i <= countPoints) {
		ch = 65;
		num = 1;
		for (i = 0; i < countPoints; i++) {
			printf("%c(%d): ", ch++, num);
			for (j = 0; j < 3; j++) {
				// Чтобы не выводило отрицательный нуль
				printf("%2g ", (fabs(setPoints[i][j]) < EPS) ? 0.0 : setPoints[i][j]);
			}
			printf("\n");
		}
	}

	
}
void ClearMemory(void** mem, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if(mem[i] != NULL)
			free(mem[i]);
	}
	if(mem != NULL)
		free(mem);
}
void MemCheck(void* mem) {
	if (mem == NULL) {
		printf("\nMemory not alocated!\n");
		exit(0);
	}
}
