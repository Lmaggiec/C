#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int rowA, rowB, colA, colB;
	int **matrixA, **matrixB, **result;
	FILE* fptr;
	fptr = fopen(argv[1],"r");
	if(fptr == NULL){
       printf("error");
       return 0;
    }
    fscanf(fptr,"%d\t%d\n", &rowA, &colA);
    matrixA = (int**)malloc(rowA*sizeof(int*));
    int i, j;
    for(i=0;i<rowA;i++){
    	matrixA[i] = (int*) malloc(colA*sizeof(int*));
    }
    for(i=0;i<rowA;i++){
		for(j=0;j<colA;j++){
			fscanf(fptr, "%d", &matrixA[i][j]);
		}
	}
	fscanf(fptr,"%d\t%d\n", &rowB, &colB);
    matrixB = (int**)malloc(rowB*sizeof(int*));
    for(i=0;i<rowB;i++){
    	matrixB[i] = (int*) malloc(colB*sizeof(int*));
    }
	for(i=0;i<rowB;i++){
		for(j=0;j<colB;j++){
			fscanf(fptr, "%d", &matrixB[i][j]);
		}
	}
	if(colA != rowB){
		printf("bad-matrices");
		return 0;
	}
    result = (int**)malloc(rowA*sizeof(int*));
	for(i=0;i<rowA;i++){
    	result[i] = (int*) malloc(colB*sizeof(int*));
    }
    int k;
	for(i=0;i<rowA;i++){
		for(j=0;j<colB;j++){
			result[i][j] = 0;
			for(k=0;k<colA;k++){
				result[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
  
	for(i=0;i<rowA;i++){
		for(j=0;j<colB;j++){
			printf("%d\t",result[i][j]);
		}
		printf("\n");
	}

	return 0;
}