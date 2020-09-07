#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define POLY_SIZE 6

int method_flag = 0;
void (*convert_to_array)(int *poly_coef, int **poly_array);
void (*padd)(int *poly1, int *poly2, int **poly_result);

enum method_index {
	INDEX_1 = 1,
	INDEX_2
};

void padd_1(int *poly1, int *poly2, int **poly_result)
{
	char flag;
	int i, count;
	int fir_i, fir_m, sec_i, sec_m, res_i;
	int hash[POLY_SIZE];

	memset(hash, 0, sizeof(hash));

	for (i = 1; i < (poly1[0] * 2); i += 2) {
		hash[poly1[i]] |= 1;
	}

	for (i = 1; i < (poly2[0] * 2); i += 2) {
		hash[poly2[i]] |= 1;
	}

	for (i = 0, count = 0; i < POLY_SIZE; i++) {
		if (hash[i] != 0)
			count++;
	}

	*poly_result = (int *)calloc((count * 2) + 1, sizeof(int));

	fir_i = sec_i = res_i = 1;
	fir_m = poly1[0] * 2;
	sec_m = poly2[0] * 2;

	while (fir_i <= fir_m && sec_i <= sec_m) {
		flag = (poly1[fir_i] > poly2[sec_i]) ? '>' : (poly1[fir_i] == poly2[sec_i]) ? '=' : '<';
		switch (flag) {
		case '>':
			(*poly_result)[res_i++] = poly1[fir_i++];
			(*poly_result)[res_i++] = poly1[fir_i++];
			break;
		case '=':
			(*poly_result)[res_i + 1] = poly1[fir_i + 1] + poly2[sec_i + 1];
			if ((*poly_result)[res_i + 1] != 0) {
				(*poly_result)[res_i] = poly1[fir_i];
				res_i += 2;
			}
			fir_i += 2;
			sec_i += 2;
			break;
		case '<':
			(*poly_result)[res_i++] = poly2[sec_i++];
			(*poly_result)[res_i++] = poly2[sec_i++];
			break;
		}
	}

	while (fir_i <= fir_m) {
		(*poly_result)[res_i++] = poly1[fir_i++];
		(*poly_result)[res_i++] = poly1[fir_i++];
	}

	while (sec_i <= sec_m) {
		(*poly_result)[res_i++] = poly2[sec_i++];
		(*poly_result)[res_i++] = poly2[sec_i++];
	}

	(*poly_result)[0] = (res_i - 1) / 2;
}

void convert_to_array_1(int *poly_coef, int **poly_array)
{
	int i, count;

	count = 0;
	for (i = (POLY_SIZE - 1); i >= 0; i--) {
		if (poly_coef[i] != 0)
			count++;
	}

	*poly_array = (int *)calloc((count * 2) + 1, sizeof(int));

	(*poly_array)[0] = count;

	count = 1;
	for (i = (POLY_SIZE - 1); i >= 0; i--) {
		if (poly_coef[i] != 0) {
			(*poly_array)[count++] = i;
			(*poly_array)[count++] = poly_coef[i];
		}
	}

}

void print_array(int *poly_array)
{
	int i;
	for (i = 0; i < (poly_array[0] * 2) + 1; i++) {
		printf("%2d ", poly_array[i]);
	}
	printf("\n");
}

void print_poly(int *poly)
{
	int i;
	for (i = (POLY_SIZE - 1); i > 0; i--) {
		if (poly[i])
			printf("%2dx^%d + ", poly[i], i);
	}
	printf("%d\n", poly[i]);
}

int parse_method(int argc, char **argv)
{
	if (argc != 2)
		return 0;

	if (!strcmp(argv[1], "1")) {
		method_flag = INDEX_1;
		convert_to_array = convert_to_array_1;
		padd = padd_1;
	} else if (!strcmp(argv[1], "2")) {
		method_flag = INDEX_2;
	}

	return (method_flag != 0);
}

int main(int argc, char **argv)
{
	int i, j;
	int poly_coefs[3][POLY_SIZE];
	int *poly_array[3];

	if (!parse_method(argc, argv)) {
		printf("Please input the method: \"1\" or \"2\".\n");
		return -EINVAL;
	}

	srand(time(NULL));

	/* Initialize the polynomial */
	for (i = 0; i < 2; i++) {
		for (j = 0; j < POLY_SIZE; j++) {
			poly_coefs[0][j] = (rand() % 20) - 10;
			poly_coefs[1][j] = (rand() % 20) - 10;
		}
	}

	/* Print the polynomial */
	for (i = 0; i < 2; i++) {
		printf("p%d = ", i);
		print_poly(poly_coefs[i]);
	}

	/* Convert to array */
	if(convert_to_array == NULL) {
		printf("func: convert_to_array is NULL\n");
		return 0;
	}

	for (i = 0; i < 2; i++) {
		convert_to_array(poly_coefs[i], &poly_array[i]);
	}

	/* Print the array */
	for (i = 0; i < 2; i++) {
		printf("array%d = ", i);
		print_array(poly_array[i]);
	}

	if(padd == NULL) {
		printf("func: padd is NULL\n");
		return 0;
	}

	padd(poly_array[0], poly_array[1], &poly_array[2]);

	printf("array  = ");
	print_array(poly_array[2]);

	for (i = 0; i < 2; i++) {
		free(poly_array[i]);
	}

	return 0;
}
