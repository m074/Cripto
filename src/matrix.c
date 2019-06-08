#define SUCCESS 1
#define FAILURE !SUCCESS

#include <stdlib.h>

// static const int inverses[] = {1, 126, 84, 63, 201, 42, 36, 157, 28, 226, 137, 21, 58, 18, 67, 204, 192, 14, 185, 113,
// 12, 194, 131, 136, 241, 29, 93, 9, 26, 159, 81, 102, 213, 96, 208, 7, 95, 218, 103, 182, 49, 6, 216, 97, 106, 191, 235,
// 68, 41, 246, 64, 140, 90, 172, 178, 130, 229, 13, 234, 205, 107, 166, 4, 51, 112, 232, 15, 48, 211, 104, 99, 129, 196,
// 173, 164, 109, 163, 177, 197, 91, 31, 150, 124, 3, 189, 108, 176, 174, 110, 53, 80, 221, 27, 243, 37, 34, 44, 146, 71,
// 123, 169, 32, 39, 70, 153, 45, 61, 86, 76, 89, 199, 65, 20, 240, 227, 132, 118, 117, 135, 228, 195, 179, 100, 83, 249,
// 2, 168, 151, 72, 56, 23, 116, 134, 133, 119, 24, 11, 231, 186, 52, 162, 175, 165, 190, 206, 98, 181, 212, 219, 82, 128,
// 180, 105, 207, 217, 214, 8, 224, 30, 171, 198, 141, 77, 75, 143, 62, 248, 127, 101, 220, 160, 54, 74, 88, 142, 87, 78,
// 55, 122, 152, 147, 40, 203, 236, 19, 139, 200, 247, 85, 144, 46, 17, 238, 22, 121, 73, 79, 161, 111, 187, 5, 210, 183, 
// 16, 60, 145, 154, 35, 245, 202, 69, 148, 33, 156, 244, 43, 155, 38, 149, 170, 92, 225, 242, 158, 222, 10, 115, 120, 57,
// 239, 138, 66, 237, 59, 47, 184, 233, 193, 230, 114, 25, 223, 94, 215, 209, 50, 188, 167, 125, 250};

typedef struct matrix {
	int rows;
	int columns;
	int ** data;
} matrix;

int inverse(int i);
matrix* newMatrix(int rows, int columns);
int isDependent(int a, int b);
matrix* randomMatrix(int n, int k);
void matrixMuduleN(Matrix *m, int n);
void coFactorMatrix(Matrix *m, Matrix *temp, int p, int q, int n);
int determinant(Matrix *m, int n);
Matrix *adjoint(Matrix *m);

void setSeed(int64_t s);
uint8_t nextChar(void);

void freeMatrix(Matrix *matrix)
{
	for(int i=0; i<matrix->rows; i++){
		for(int j=0; j<matrix->columns; j++){
		free(matrix->data[i][j]);
		}
		free(matrix->data[i]);
	}
	free(matrix->data);
	free(matrix);
}

matrix* newMatrix(int rows, int columns) {
	matrix new;

	new = malloc(sizeof(Matrix));
	if(!resultado) {
		exit(FAILURE);
	}

	new->rows = rows;
	new->columns = columns;

	new->data = malloc(sizeof(int*) * new->rows);
	if(!new->data) {
		exit(FAILURE);
	}

	for(i=0; i<rows; i++){
		new->data[i] = malloc(sizeof(int*) * new->columns);
		if(!new->data[i]) {
		exit(FAILURE);
		}
		for(int j=0; j<new->columns; j++) {
			mpz_init(new->data[i][j]);
		}
	}
	return new;
} 

matrix* randomMatrix(int n, int k) {
	matrix new;

	new = malloc(sizeof(Matrix));
	if(!resultado) {
		exit(FAILURE);
	}

	new->rows = rows;
	new->columns = columns;

	new->data = malloc(sizeof(int*) * new->rows);
	if(!new->data) {
		exit(FAILURE);
	}

	for(i=0; i<n; i++){

		new->data[i] = malloc(sizeof(int*) * new->columns);
		if(!new->data[i]) {
		exit(FAILURE);
		}

		for(j=0; j<k; j++){
			new->data[i][j] = nextChar%251;
		}
	}
	return new;
} 

void matrixMuduleN(Matrix *m, int n){
	for(i=0; i<m->rows; i++) {
		for(j=0; j<m->columns; j++) {
			m->data[i][j]%=n;
		}
	}
}

matrix* transposeMatrix(Matrix *m) {
	matrix new;

	new = malloc(sizeof(Matrix));
	if(!resultado) {
		exit(FAILURE);
	}

	new->rows = rows;
	new->columns = columns;

	new->data = malloc(sizeof(int*) * new->rows);
	if(!new->data) {
		exit(FAILURE);
	}

	for(i=0; i<m->rows; i++){

		new->data[i] = malloc(sizeof(int*) * new->columns);
		if(!new->data[i]) {
		exit(FAILURE);
		}

		for(j=0; j<m->columns; j++){
			new->data[j][i] = m->data[i][j];
		}
	}
	return new;
} 

/* Code for cofactor and adj is based on https://www.geeksforgeeks.org/adjoint-inverse-matrix/ */

void coFactorMatrix(Matrix *m, Matrix *temp, int p, int q, int n) {
	int i = 0, j = 0; 
  
    // Looping for each element of the matrix 
    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        { 
            //  Copying into temporary matrix only those element 
            //  which are not in given row and column 
            if (row != p && col != q) 
            { 
                temp->data[i][j++] = m->data[row][col]; 
  
                // Row is filled, so increase row index and 
                // reset col index 
                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 

int determinant(Matrix *m, int n) 
{ 
    int D = 0; // Initialize result 
  
    //  Base case : if matrix contains single element 
    if (n == 1) 
        return m->data[0][0]; 
  
  	Matrix temp = newMatrix(m->rows,m->columns);
    // To store cofactors 
  
    int sign = 1;  // To store sign multiplier 
  
     // Iterate for each element of first row 
    for (int f = 0; f < n; f++) 
    { 
        // Getting Cofactor of A[0][f] 
        getCofactor(m, temp, 0, f, n); 
        D += sign * m->data[0][f] * determinant(temp, n - 1); 
  
        // terms are to be added with alternate sign 
        sign = -sign; 
    } 

    freeMatrix(temp);
  
    return D; 
} 

Matrix *adjoint(Matrix *m) { 

	Matrix adj = newMatrix(m->rows,m->columns);

    if (m->rows == 1) 
    { 
        adj->data[0][0] = 1; 
        return; 
    } 
  
    // temp is used to store cofactors of A[][] 
    int sign = 1;
    Matrix temp = newMatrix(m->rows,m->columns); 
  
    for (int i=0; i<N; i++) 
    { 
        for (int j=0; j<N; j++) 
        { 
            // Get cofactor of A[i][j] 
            getCofactor(A, temp, i, j, N); 
  
            // sign of adj[j][i] positive if sum of row 
            // and column indexes is even. 
            sign = ((i+j)%2==0)? 1: -1; 
  
            // Interchanging rows and columns to get the 
            // transpose of the cofactor matrix 
            adj[j][i] = (sign)*(determinant(temp, N-1)); 
        } 
    } 
    freeMatrix(temp);
    return adj;
} 

// int inverse(int i) {
//   i %= 251;	
//   return inverses[i - 1];
// }

void setSeed(int64_t s) {
 	seed = (s ^ 0x5DEECE66DL) & ((1LL << 48) - 1);
}

uint8_t nextChar(void) {
 	seed = (seed * 0x5DEECE66DL + 0xBL) & ((1LL << 48) - 1);
 	return (uint8_t)(seed>>40);
} 