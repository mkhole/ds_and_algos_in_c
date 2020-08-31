#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 6

void print_matrix(int (*matrix)[MATRIX_SIZE]) {
	int i, j;

	if(matrix == NULL) 
		return;

	for(i=0; i<MATRIX_SIZE; i++) {
		for(j=0; j<MATRIX_SIZE; j++) {
			printf("%2d ", *(*(matrix + i) + j));
		}
		printf("\n");
	}
	printf("\n");
}

void print_array(int *array, int size) {
	int i;
	
	if(array == NULL)
		return;

	for(i=0; i<size; i++) {
		printf("%2d ", *(array + i));
	}
	printf("\n\n");
}

int main() {
	int *array;
	int matrix[MATRIX_SIZE][MATRIX_SIZE];
	int i, j, num, arr_size;

	arr_size = (MATRIX_SIZE * (MATRIX_SIZE + 1)) / 2;
	array = (int *)calloc(arr_size, sizeof(int));

	/* Fill in the matrix */
	num = 1;
	for(i=0; i<MATRIX_SIZE; i++) {
		for(j=0; j<MATRIX_SIZE; j++) {
			if(i <= j)
				matrix[i][j] = num++;
			else
				matrix[i][j] = 0;
		}
	}

	print_matrix(matrix);

	/* Convert to arry */
	num = 0;
	for(i=0; i<MATRIX_SIZE; i++) {
		for(j=0; j<MATRIX_SIZE; j++) {
			if(matrix[i][j] != 0)
				array[num++] = matrix[i][j];
		}
	}

	print_array(array, arr_size);

	/* Get the matrix(i, j) from array */
	i = 2;
	j = 4;

	num = MATRIX_SIZE * (i) - (((i + 1) * (i)) / 2) + j;

	printf("matrix[%d][%d]: %2d\n", i, j, matrix[i][j]);
	printf("array[%d]: %2d\n", num, array[num]);

	free(array);

    return 0;
}
