#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define MATRIX_SIZE 6

int method_flag = -1;

enum method_index {
	INDEX_UPPER,
	INDEX_LOWER
};

void print_matrix(int (*matrix)[MATRIX_SIZE])
{
	int i, j;

	if (matrix == NULL)
		return;

	for (i = 0; i < MATRIX_SIZE; i++) {
		for (j = 0; j < MATRIX_SIZE; j++) {
			printf("%2d ", *(*(matrix + i) + j));
		}
		printf("\n");
	}
	printf("\n");
}

void print_array(int *array, int size)
{
	int i;

	if (array == NULL)
		return;

	for (i = 0; i < size; i++) {
		printf("%2d ", *(array + i));
	}
	printf("\n\n");
}

int compare(int a, int b)
{
	int result = 0;

	switch (method_flag) {
	case INDEX_UPPER:
		result = (a <= b);
		break;
	case INDEX_LOWER:
		result = (a >= b);
		break;
	}

	return result;
}

int num_in_array(int i, int j)
{
	int num = 0;

	switch (method_flag) {
	case INDEX_UPPER:
		num = MATRIX_SIZE * (i) - (((i + 1) * (i)) / 2) + j;
		break;
	case INDEX_LOWER:
		num = (((i + 1) * (i)) / 2) + j;
		break;
	}

	return num;
}

void parse_method(int argc, char **argv)
{
	if (argc != 2)
		return;

	if (!strcmp(argv[1], "upper")) {
		method_flag = INDEX_UPPER;
	} else if (!strcmp(argv[1], "lower")) {
		method_flag = INDEX_LOWER;
	}
}

int main(int argc, char **argv)
{
	int *array;
	int matrix[MATRIX_SIZE][MATRIX_SIZE];
	int i, j, num, arr_size;

	srand(time(NULL));

	parse_method(argc, argv);

	if (method_flag == -1) {
		printf("Please input the method: \"upper\" or \"lower\".\n");
		return -EINVAL;
	}

	arr_size = (MATRIX_SIZE * (MATRIX_SIZE + 1)) / 2;
	array = (int *)calloc(arr_size, sizeof(int));

	if (array == NULL) {
		printf("Out of memory\n");
		return -ENOMEM;
	}

	/* Fill in the matrix */
	num = 1;
	for (i = 0; i < MATRIX_SIZE; i++) {
		for (j = 0; j < MATRIX_SIZE; j++) {
			if (compare(i, j))
				matrix[i][j] = num++;
			else
				matrix[i][j] = 0;
		}
	}

	print_matrix(matrix);

	/* Convert to arry */
	num = 0;
	for (i = 0; i < MATRIX_SIZE; i++) {
		for (j = 0; j < MATRIX_SIZE; j++) {
			if (matrix[i][j] != 0)
				array[num++] = matrix[i][j];
		}
	}

	print_array(array, arr_size);

	/* Randomly choose a non-zero position */
	do {
		i = rand() % MATRIX_SIZE;
		j = rand() % MATRIX_SIZE;
	} while (matrix[i][j] == 0);

	/* Get the position of matrix(i, j) in the array */
	num = num_in_array(i, j);

	printf("matrix[%d][%d]: %2d\n", i, j, matrix[i][j]);
	printf("array[%d]: %2d\n", num, array[num]);

	free(array);
	return 0;
}
