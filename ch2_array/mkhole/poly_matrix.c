#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define POLY_SIZE 6

void print_matrix(int (*matrix)[POLY_SIZE])
{
	int i, j;

	printf("\t");
	for (i = 0; i < POLY_SIZE; i++) {
		printf("y%d\t", i);
	}
	printf("\n");

	for (i = 0; i < POLY_SIZE; i++) {
		printf("x%d\t", i);
		for (j = 0; j < POLY_SIZE; j++) {
			printf("%2d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void convert_matrix(int (*poly)[POLY_SIZE], int (*matrix)[POLY_SIZE])
{
	int i;
	int x_pos, y_pos, coeff;

	for (i = 0; i < POLY_SIZE; i++) {
		x_pos = poly[0][i];
		y_pos = poly[1][i];
		coeff = poly[2][i];
		matrix[x_pos][y_pos] = coeff;
	}
}

void print_poly(int (*poly)[POLY_SIZE])
{
	int i, flag = 0;

	for (i = 0; i < POLY_SIZE; i++) {
		if (poly[2][i] == 0)
			continue;

		if (flag)
			printf(" + ");

		printf("%d(x^%d)(y^%d)", poly[2][i], poly[0][i], poly[1][i]);
		flag |= 1;
	}
	printf("\n");
}

void shuffle_array(int (*array)[POLY_SIZE])
{
	int i, temp, seed;

	for (i = 0; i < POLY_SIZE; i++) {
		seed = rand() % POLY_SIZE;
		temp = (*array)[i];
		(*array)[i] = (*array)[seed];
		(*array)[seed] = temp;
	}
}

int main(int argc, char **argv)
{
	int i;
	int poly_array[3][POLY_SIZE];
	int matrix[POLY_SIZE][POLY_SIZE];

	srand(time(NULL));

	/* Initialize the polynomial
	 * [0] : Exponential of x
	 * [1] : Exponential of y
	 * [2] : Coefficient of each position
	 */
	for (i = 0; i < POLY_SIZE; i++) {
		poly_array[0][i] = i;
		poly_array[1][i] = i;
		poly_array[2][i] = rand() % 10;
	}

	for (i = 0; i < 2; i++) {
		shuffle_array(&poly_array[i]);
	}

	print_poly(poly_array);

	memset(matrix, 0, sizeof(matrix));
	convert_matrix(poly_array, matrix);

	print_matrix(matrix);

	return 0;
}
