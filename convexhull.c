#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>

/* Point designation */
typedef struct point {
    int x, y, z;
}point_t;


int check_potential_faces(int , point_t *);
/* Global vars */


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
            points = (point_t*)malloc(size * sizeof(point_t));
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
	// abcd - коэффициенты уравнения плоскости
	int check, problem, freeCoef;
	int i, j, k;
	// Так удобнее будет считать
	point_t vectA, vectB, normVect;

	for(i = 0; i < countPoints; i++) {
		for(j = i+1; j < countPoints; j++) {
			vectA.x = Points[j].x - Points[i].x;
			vectA.y = Points[j].y - Points[i].y;
			vectA.z = Points[j].z - Points[i].z;

			for(k = j+1; k < countPoints; k++) {
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
				freeCoef = normVect.x*Points[i].x + normVect.y*Points[i].y + normVect.z*Points[i].z;
				
			}
		}
	}

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