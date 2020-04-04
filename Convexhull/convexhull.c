#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#define swap(t,a,b) {t temp; temp = a; a = b; b = temp;}

/* Point designation */
typedef struct point {
	int x, y, z;
}point_t;

/* Inequality designation */
typedef struct inequal {
	int coeff[4];
}Inequal_t;

/* Global vars */
int countIneq = 0, countPoints = 0;
Inequal_t* arrIneq;
point_t* setPoints;
point_t tmpPoint;
double* x;

/* Convex Hull (A) Functions */
// Face finding function
int check_potential_faces(int);
// The function of finding the ratio of the inequality coefficients
int determinate_rate_ineq(int*);
// Linear inequality check function
int check_linear_dep(int*);

int Calc_Point(Inequal_t , Inequal_t , Inequal_t );
void vertex_enumeration();

/* Utilities Functions */
// Input Files (main func)
int inputFiles(int , char* );
// NOD search
int NOD(int, int);
// Check memory allocation
void MemCheck(void*);
// Input inequality
void print_ineq(Inequal_t*);
int Gauss(int**, int*, int);


int main(int argc, char* argv[]) {
	inputFiles(argc, argv);

	if (setPoints != NULL) {
		free(setPoints);
		setPoints = NULL;
	}
	if (arrIneq != NULL) {
		free(arrIneq);
		arrIneq = NULL;
	}
	
	return 0;
}

int inputFiles(int argc, char* argv[]) {
	int i, j, size;
	char modeWork;
	point_t points;
	Inequal_t tmp;
	int **arrayTemp;

	FILE *fp = NULL;

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

			setPoints = (point_t*)malloc(size * sizeof(point_t));
			MemCheck(setPoints);

			// Input and Output Dots
			for (i = 0; i < size; i++) {
				if (!(fscanf(fp, "%d%d%d", &points.x, &points.y, &points.z))) {
					printf("\nIncorrect coordinate\n");
					return 1;
				}
				setPoints[i].x = points.x;
				setPoints[i].y = points.y;
				setPoints[i].z = points.z;
				printf("%d %d %d\n", setPoints[i].x, setPoints[i].y, setPoints[i].z);
			}
			check_potential_faces(size);
			printf("Number of Faces: %d\n", countIneq);
			print_ineq(arrIneq);

			countIneq = 0;
			break;

		// Hyperplane
		case 'H':
			printf("\nSelected type H\n");

			arrIneq = (Inequal_t*)malloc(size * sizeof(Inequal_t));
			if (!arrIneq) return 1;

			countIneq = size;

			for (i = 0; i < size; i++) {
				if (!(fscanf(fp, "%d%d%d%d", &tmp.coeff[0], &tmp.coeff[1], &tmp.coeff[2], &tmp.coeff[3]))) {
					printf("\nIncorrect coefficient\n");
					return 1;
				}
				for (j = 0; j < 3; j++) {
					arrIneq[i].coeff[j] = tmp.coeff[j];
				}
				arrIneq[i].coeff[3] = tmp.coeff[3];
				
			}
			print_ineq(arrIneq);
			
			vertex_enumeration();

			break;

		// Error
		default:
			printf("\nType not selected or invalid type\n");
			return 1;
		}

		/*
		vertexEnum(f, typeIn);
		// Строим граф
		skeleton();
		*/
	}

	fclose(fp);
	return 0;
}

/* Convex Hull (A) Functions */
int check_potential_faces(int countPoints) {

	int freeCoeff, check, halfspace, oops, sign, rate;
	int i, j, k, p, q;

	int tmp[4];
	sign = 1;
	// Система неравенств
	arrIneq = (Inequal_t*)malloc(countPoints * sizeof(Inequal_t));
	MemCheck(arrIneq);

	halfspace = 0;

	// Так удобнее будет считать
	point_t vectA, vectB, normVect;

	for (i = 0; i < countPoints; i++) {
		for (j = 0; j < countPoints; j++) {
			if (j == i) continue;
			vectA.x = setPoints[j].x - setPoints[i].x;
			vectA.y = setPoints[j].y - setPoints[i].y;
			vectA.z = setPoints[j].z - setPoints[i].z;

			for (k = 0; k < countPoints; k++) {
				if (k == j || k == i) continue;
				vectB.x = setPoints[k].x - setPoints[i].x;
				vectB.y = setPoints[k].y - setPoints[i].y;
				vectB.z = setPoints[k].z - setPoints[i].z;
				/*
							   | x   y   z |
				vectA x vectB: |vA1 vA2 vA3| = ax+by+cz
							   |vB1 vB2 vB3|
				*/
				normVect.x = vectA.y * vectB.z - vectA.z * vectB.y;
				normVect.y = vectA.z * vectB.x - vectA.x * vectB.z; // Если посмотреть на определитель
				normVect.z = vectA.x * vectB.y - vectA.y * vectB.x;
				freeCoeff = normVect.x * -setPoints[i].x + normVect.y * -setPoints[i].y + normVect.z * -setPoints[i].z;

				// Смотрим на оставшиеся точки
				halfspace = 0;
				oops = 0;
				for (p = 0; p < countPoints; p++) {
					if (p == k || p == i || p == j) continue;
					// Подставим точку в наше уравнение плоскости
					check = normVect.x * setPoints[p].x + normVect.y * setPoints[p].y + normVect.z * setPoints[p].z + freeCoeff;

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
				if(!oops) {
					if (halfspace > 0)
						sign = -1;
					else
						if (halfspace < 0)
							sign = 1;
					tmp[0] = sign * normVect.x;
					tmp[1] = sign * normVect.y;
					tmp[2] = sign * normVect.z;
					tmp[3] = sign * freeCoeff;
				}

				if (!(check_linear_dep(tmp)) && (!oops)) {

					rate = determinate_rate_ineq(tmp);
					if (rate != 0)
						for (q = 0; q < 4; q++)
							tmp[q] /= rate;

					arrIneq[countIneq].coeff[0] = tmp[0];
					arrIneq[countIneq].coeff[1] = tmp[1];
					arrIneq[countIneq].coeff[2] = tmp[2];
					arrIneq[countIneq].coeff[3] = tmp[3];
					countIneq++;
				}

			}
		}
	}

	return 0;
}
int determinate_rate_ineq(int* tmp) {
	int rate;

	rate = NOD(NOD(abs(tmp[0]), abs(tmp[1])), NOD(abs(tmp[2]), abs(tmp[3])));
	return rate;
}
int check_linear_dep(int* tmp) {
	int i, j, count1, rate;

	rate = determinate_rate_ineq(tmp);

	if (!rate)
		return 1;

	for (i = 0; i < countIneq; i++) {
		count1 = 0;
		for (j = 0; j < 4; j++) {
			if ((tmp[j] / rate) == arrIneq[i].coeff[j])
				count1++;
		}
		if (count1 == 4)
			return 1;
	}

	return 0;
}

/* Vertex Enumeration (B1) Functions */
void vertex_enumeration() {
	int i, j, p, check;
	int** arrayTemp, *b;
	point_t point;
	
	setPoints = (point_t*)malloc(countIneq * sizeof(point_t));
	if (!setPoints) return;

	b = (int*)malloc(3 * sizeof(int));
	if (!b) return;

	arrayTemp = (int**)malloc(3 * sizeof(int));
	if (!arrayTemp) return;
	for (i = 0; i < 3; i++) {
		arrayTemp[i] = (int*)malloc(4 * sizeof(int));
		if (!arrayTemp[i]) return;
	}

	x = (double*)malloc(3 * sizeof(double));
	if (!x) return;

	for (i = 0; i < countIneq; i++) {
		for (j = 0; j < countIneq; j++) {
			if (j <= i) continue;
			for (p = 0; p < countIneq; p++) {
				if (p <= j || p <= i) continue;

				if (check = Calc_Point(arrIneq[i], arrIneq[j], arrIneq[p], arrayTemp, b))
					continue;
				else
					if(!check_ident_point(tmpPoint)) {
						setPoints[countPoints] = tmpPoint;
						countPoints++;
					}
			}
		}
	}

	for (i = 0; i < countPoints; i++)
		printf("%d %d %d\n", setPoints[i].x, setPoints[i].y, setPoints[i].z);

	for (i = 0; i < 3; i++)
		free(arrayTemp[i]);
	free(arrayTemp);
	
}

int check_ident_point(point_t point) {
	int i;

	for (i = 0; i < countPoints; i++) {
		if (setPoints[i].x == point.x && setPoints[i].y == point.y && setPoints[i].z == point.z)
			return 1;
	}

	return 0;
}

int Calc_Point(Inequal_t ineq1, Inequal_t ineq2, Inequal_t ineq3, int** arrayTemp, int *b) {
	int i, j;

	for (j = 0; j < 3; j++) {
		arrayTemp[0][j] = ineq1.coeff[j];
		arrayTemp[1][j] = ineq2.coeff[j];
		arrayTemp[2][j] = ineq3.coeff[j];
	}
	b[0] = ineq1.coeff[3];
	b[1] = ineq2.coeff[3];
	b[2] = ineq3.coeff[3];

	if (Gauss(arrayTemp, b, 3)) {
		return 1;
	}
	else {
		tmpPoint.x = x[0];
		tmpPoint.y = x[1];
		tmpPoint.z = x[2];
	}
	
	return 0;
}

int Gauss(int** a, int *b, int n) {
	int i, j, k, cf, check;
	int idx;
	double EPS = 0.00001;
	double max;
	check = 0;
	
	k = 0;
	while (k < n) {
		max = abs(a[k][k]);
		idx = k;
		for (i = k + 1; i < n; i++) {
			if (abs(a[i][k]) > max) {
				max = abs(a[i][k]);
				idx = i;
			}
		}

		if (max < EPS)
			return 1;

		for (j = 0; j < n; j++)
			swap(int, a[k][j], a[idx][j]);
		swap(int, b[k], b[idx]);

		for (i = k; i < n; i++) {
			cf = a[i][k];
			if (abs(cf) < EPS) continue;

			for (j = 0; j < n; j++)
				a[i][j] = a[i][j] / cf;
			b[i] = b[i] / cf;

			if (i == k)  continue;

			for (j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			b[i] = b[i] - b[k];
		}
		k++;
	}

	for (k = n - 1; k >= 0; k--) {
		x[k] = b[k];
		for (int i = 0; i < k; i++)
			b[i] = b[i] - a[i][k] * x[k];
	}
	
	return 0;
}



/* Utilities Functions */
void print_ineq(Inequal_t* Ineq) {
	int i, j;
	char ch[] = { 'x', 'y', 'z', '\0' };

	for (i = 0; i < countIneq; i++) {
		for (j = 0; j < 3; j++) {
			if (Ineq[i].coeff[j] != 0) {
				if (Ineq[i].coeff[j] == 1 && j != 0)
					printf("+%c", ch[j]);

				if (Ineq[i].coeff[j] == 1 && j == 0)
					printf("%c", ch[j]);

				if (Ineq[i].coeff[j] == -1)
					printf("-%c", ch[j]);

				if (Ineq[i].coeff[j] > 1 && j != 0)
					printf("+%d%c", Ineq[i].coeff[j], ch[j]);

				if (Ineq[i].coeff[j] > 1 && j == 0)
					printf("%d%c", Ineq[i].coeff[j], ch[j]);

				if (Ineq[i].coeff[j] < -1)
					printf("%d%c", Ineq[i].coeff[j], ch[j]);
			}
		}
		// Минус так как переносим в правую часть неравенства
		printf("<=%d\n", -Ineq[i].coeff[3]);
	}
}
int NOD(int a, int b) {
	if (a == 0 || b == 0)
		return a + b;
	if (a > b)
		return NOD(a - b, b);
	else
		return NOD(a, b - a);
}
void MemCheck(void *mem) {
	if (mem == NULL) {
		printf("\nMemory not alocated!\n");
		exit(0);
	}
}

 
