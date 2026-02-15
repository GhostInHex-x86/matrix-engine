#include <stdio.h>
#include <stdlib.h>

void add(int rsize, int csize, int (*a)[csize], int (*b)[csize], int (*c)[csize]) {
	for (int i = 0; i < rsize; i++) {
		for (int j = 0; j < csize; j++) c[i][j] = a[i][j] + b[i][j];
	}
}

void sub(int rsize, int csize, int (*a)[csize], int (*b)[csize], int (*c)[csize]) {
	for (int i = 0; i < rsize; i++) {
		for (int j = 0; j < csize; j++) c[i][j] = a[i][j] - b[i][j];
	}
}

void trans(int rsize, int csize, int (*mat)[csize], int (*c)[csize]) {
	for (int i = 0; i < csize; i++) {
		for (int j = 0; j < rsize; j++) c[i][j] = mat[j][i];
	}
}

void mult(int r1size, int c1size, int c2size, int (*a)[c1size], int (*b)[c2size], int (*c)[c2size]) {
	for (int i = 0; i < r1size; i++) {
		for (int j = 0; j < c2size; j++) {
			int sum = 0;
			for (int k = 0; k < c1size; k++) sum += a[i][k] * b[k][j];
			c[i][j] = sum;
		}
	}
}

int det(int size, int (*mat)[size]) {
	if (size == 1) return mat[0][0];
	if (size == 2) return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

	int submat[size-1][size-1], deter = 0;
	for (int mcol = 0; mcol < size; mcol++) {
		for (int r = 1; r < size; r++) {
			int mscol = 0;
			for (int c = 0; c < size; c++) {
				if (c == mcol) continue;
				submat[r-1][mscol++] = mat[r][c];
			}
		}
		int sign = (mcol % 2 == 0) ? 1: -1;
		deter += sign * mat[0][mcol] * det(size-1, submat); 
	}
	return deter;
}

void printm(int rsize, int csize, int (*r)[csize]) {
	printf("\nRESULT:\n");
	for(int i = 0; i < rsize; i++) {
		for (int j = 0; j < csize; j++) printf("%d ", r[i][j]);
		putchar('\n');
	}
}

void failedAlloc() {
	printf("[-] Memory allocation failed for array!");
	exit(EXIT_FAILURE);
}


int main() {
	char buffer[255];
	int rs1, cs1, rs2, cs2, mat, op;

	printf("Enter matrix 1 dimension[3x3, 2x2, 2x3...]: ");
	scanf("%254s", buffer);
	sscanf(buffer, "%dx%d", &rs1, &cs1);
	int (*a)[cs1] = malloc(rs1 * sizeof *a);
	if (a == NULL) failedAlloc();

	printf("Enter the matrix 1:\n");
	for (int i = 0; i < rs1; i++) {
		printf("Enter row %d: ", i+1);
		for (int j = 0; j < cs1; j++) scanf("%d", &a[i][j]);
	}
		
	printf("Enter matrix 2 dimension[3x3, 2x2, 2x3...]: ");
	scanf("%254s", buffer);
	sscanf(buffer, "%dx%d", &rs2, &cs2);
	int (*b)[cs2] = malloc(rs2 * sizeof *b);
	if (b == NULL) failedAlloc();

	printf("\nEnter the matrix 2:\n");
	for (int i = 0; i < rs2; i++) {
		printf("Enter row %d: ", i+1);
		for (int j = 0; j < cs2; j++) scanf("%d", &b[i][j]);
	}

	printf("\nMENU:\n \
		[1] Addition\n \
		[2] Subtraction\n \
		[3] Transpose\n \
		[4] Multiplication\n \
		[5] Determinant\n \
		\nEnter Choice: ");
	scanf("%1d", &op);

	switch (op) {
		case 1: {
				if (rs1!=rs2 || cs1!=cs2){
					printf("\n[!] Invalid dimensions to perform addition!\n");
					exit(EXIT_FAILURE);
				}
				int (*c)[cs1] = malloc(rs1 * sizeof *c);
				if (c == NULL) failedAlloc();

				add(rs1, cs1, a, b, c);
				printm(rs1, cs1, c);
				free(c);
				break;
			}
		case 2: {
				if (rs1!=rs2 || cs1!=cs2){
					printf("\n[!] Invalid dimensions to perform subtraction!\n");
					exit(EXIT_FAILURE);
				}
				int (*c)[cs1] = malloc(rs1 * sizeof *c);
				if (c == NULL) failedAlloc();

				sub(rs1, cs1, a, b, c);
				printm(rs1, cs1, c);
				free(c);
				break;
			}
		case 3: {
				printf("matrix 1 or 2: ");
				scanf("%1d", &mat);

				int (*c)[cs1] = malloc(rs1 * sizeof *c);
				if (mat == 1) trans(rs1, cs1, a, c);
				else if (mat == 2) trans(rs2, cs2, b, c);
				else {
					printf("\n[-] Error: Invalid matrix! \n");
					exit(EXIT_FAILURE);
				}
				printm(rs1, cs1, c);
				free(c);
				break;
			}
		case 4: {
				if (cs1!=rs2) {
					printf("\n[-] Error: Invalid dimensions for multiplication!\n");
					exit(EXIT_FAILURE);
				}
				int (*c)[cs2] = malloc(rs1 * sizeof *c);		
				if (c == NULL) failedAlloc();

				mult(rs1, cs1, cs2, a, b, c);
				printm(rs1, cs2, c);
				free(c);
				break;
			}
		case 5: {
			
				printf("matrix 1 or 2: ");
				scanf("%1d", &mat);
				int determinant = 0;
				if (mat == 1 && rs1 == cs1) determinant = det(rs1, a);
				else if (mat == 2 && rs2 == cs2) determinant = det(rs2, b);
				else {
					printf("\n[-] Error: Invalid Dimensions! \n");
					exit(EXIT_FAILURE);
				}
				printf("\nDeterminant: %d\n", determinant);
				break;
			}
		default:
			printf("\n[-] Invalid Choice\n");
			exit(EXIT_FAILURE);
	}

	free(a);
	free(b);
	return 0;
}
