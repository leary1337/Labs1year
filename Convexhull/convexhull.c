#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#define OK 1
#define NOT_OK 0

/* Point designation */
typedef struct point {
    int x, y, z;
}point_t;

typedef struct sys_of_ineq {
	int coeff[4];
}sysIneq_t;

int check_potential_faces(int , point_t *);
int check_linear_dep(sysIneq_t *, point_t , int);
void print_ineq(sysIneq_t *);
/* Global vars */
int countIneq = 0;

/* Utilities Functions */
void MemCheck(void *);
void ClearMemory(void **, int );

int main(int argc, char *argv[]) {
	int i, j, size, arrayPts;
    char modeWork;
    point_t *points;

	FILE *fp = NULL;

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

    switch(modeWork) {
        case 'V':
            printf("\nSelected type V\n");
            if(!(points = (point_t*)malloc(size * sizeof(point_t))))
            	MemCheck(points);
            
            // Input and Output Dots
            for(i = 0; i < size; i++) {
                if (!(fscanf(fp, "%d%d%d", &points[i].x, &points[i].y, &points[i].z))) {
		            printf("\nIncorrect coordinate\n");
		            return 1;
	            }
                printf("%d %d %d\n", points[i].x,points[i].y, points[i].z);
            }
			int p = check_potential_faces(size, points);


            break;
        
        case 'H':
            printf("\nSelected type H\n");
            break;

        default:
            printf("\nType not selected\n");
            break;
    }

    return 0;
}

/* Convex Hull (A) Functions */
int check_potential_faces(int countPoints, point_t *Points) {
	
	int freeCoeff, numFaces, check, halfspace, oops, sign;
	int i, j, k, p;

	// Система неравенств
	sysIneq_t *Ineq;
	if(!(Ineq = (sysIneq_t*)malloc(countPoints * sizeof(sysIneq_t))))
        MemCheck(Ineq);

	numFaces = 0;
	halfspace = 0;

	// Так удобнее будет считать
	point_t vectA, vectB, normVect;

	for(i = 0; i < countPoints; i++) {
		for(j = 0; j < countPoints; j++) {
			if(j == i) continue;
			vectA.x = Points[j].x - Points[i].x;
			vectA.y = Points[j].y - Points[i].y;
			vectA.z = Points[j].z - Points[i].z;

			for(k = 0; k < countPoints; k++) {
				if(k == j || k == i) continue;
				vectB.x = Points[k].x - Points[i].x;
				vectB.y = Points[k].y - Points[i].y;
				vectB.z = Points[k].z - Points[i].z;
				/*
					 		   | x   y   z |
				vectA x vectB: |vA1 vA2 vA3| = ax+by+cz
					 		   |vB1 vB2 vB3|
				*/
				normVect.x = vectA.y*vectB.z - vectA.z*vectB.y; 
				normVect.y = vectA.z*vectB.x - vectA.x*vectB.z; // Если посмотреть на определитель
				normVect.z = vectA.x*vectB.y - vectA.y*vectB.x; 
				freeCoeff = normVect.x*-Points[i].x + normVect.y*-Points[i].y + normVect.z*-Points[i].z;
			
				// Смотрим на оставшиеся точки
				halfspace = 0;
				oops = 0;
				for(p = 0; p < countPoints; p++) {
					if(p == k || p == i || p == j) continue;
					// Подставим точку в наше уравнение плоскости
					check = normVect.x*Points[p].x + normVect.y*Points[p].y + normVect.z*Points[p].z + freeCoeff;
					
					// Проверяем в каком полупространстве лежат оставшиеся точки	
					if((halfspace == 1 && check < 0) || (halfspace == -1 && check > 0)) {
						oops = 1;
						break;
					}
					if(check > 0) 
						halfspace = 1;
					if(check < 0)
						halfspace = -1;
				}
		
				int dasd = check_linear_dep(Ineq, normVect, freeCoeff);
				printf("REZ: %d\n", dasd);
				if((!dasd) && (!oops)) {
					if(halfspace > 0)
						sign = -1;
					else
						sign = 1;

					Ineq[countIneq].coeff[0] = sign*normVect.x;
					Ineq[countIneq].coeff[1] = sign*normVect.y;
					Ineq[countIneq].coeff[2] = sign*normVect.z;
					Ineq[countIneq].coeff[3] = sign*freeCoeff;
					countIneq++;
					printf("COUNT: %d\n",countIneq);
				}
				
			}
		}
	}	
	printf("\n***********\n");
	print_ineq(Ineq);
	printf("Number of Faces: %d\n", numFaces);	
	return 0;
}

void print_ineq(sysIneq_t *Ineq) {
	int i, j;
	char ch[] = {'x', 'y', 'z', '\0'};

	for(i = 0; i < countIneq; i++) {
		for(j = 0; j < 3; j++) {
			if(Ineq[i].coeff[j] != 0) {
				if(Ineq[i].coeff[j] == 1 && j != 0)
					printf("+ %c ", ch[j]);

				if(Ineq[i].coeff[j] == 1 && j == 0)
					printf(" %c ", ch[j]);

				if(Ineq[i].coeff[j] == -1)
					printf("- %c ", ch[j]);
				
				if(Ineq[i].coeff[j] > 1 && j != 0)
					printf("+ %d%c ", Ineq[i].coeff[j], ch[j]);
				
				if(Ineq[i].coeff[j] > 1 && j == 0)
					printf(" %d%c ", Ineq[i].coeff[j], ch[j]);

				if(Ineq[i].coeff[j] < -1)
					printf(" %d%c ", Ineq[i].coeff[j], ch[j]);
				

				
			}
		}
		// Минус так как переносим в правую часть неравенства
		printf("<= %d\n", -Ineq[i].coeff[3]);
	}
}

int NOD(int a, int b) {
	if(a == 0 || b == 0)
		return a+b;
	if(a > b)
		return NOD(a-b, b);
	else
		return NOD(a, b-a);
}

// Проверка линейной зависимости 
int check_linear_dep(sysIneq_t *arrIneq, point_t normali, int freeCoeff) {
	int i, j, k, count;
	int rate1, rate2;
	
	sysIneq_t tmp; 
	tmp.coeff[0] = normali.x;
	tmp.coeff[1] = normali.y;
	tmp.coeff[2] = normali.z;
	tmp.coeff[3] = freeCoeff;
	rate1 = NOD(NOD(abs(tmp.coeff[0]), abs(tmp.coeff[1])), NOD(abs(tmp.coeff[2]), abs(tmp.coeff[3])));

	for(i = 0; i < countIneq; i++) {
		for(j = 0; j < 4; j++) {
			if((tmp.coeff[j]/rate1) == (arrIneq[i].coeff[j] /= rate1))
				count++;
		}
		if(count == 4)
			return 1;
	}

	return 0;
}

/* Utilities Functions */
void MemCheck(void *mem) {
	if (mem == NULL) {
		printf("\nMemory not alocated!\n");
		exit(0);
	}
}
void ClearMemory(void **mem, int size) {
	int i;
	for (i = 0; i < size; i++) {
		free(mem[i]);
	}
	free(mem);
}
