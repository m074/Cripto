/* matrix taken from http://theory.stanford.edu/~arbrad/pfe/06/matrix.c */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "matrix.h"
#include "random.h"
#include "utilities.h"

/* Creates a ``rows by cols'' matrix with all values 0.
 * Returns NULL if rows <= 0 or cols <= 0 and otherwise a
 * pointer to the new matrix.
 */
matrix * newMatrix(int rows, int cols) {
	if (rows <= 0 || cols <= 0) return NULL;

	// allocate a matrix structure
	matrix * m = (matrix *) malloc(sizeof(matrix));

	// set dimensions
	m->rows = rows;
	m->cols = cols;

	// allocate a double array of length rows * cols
	m->data = (__uint8_t *) malloc(rows*cols*sizeof(double));
	// set all data to 0
	int i;
	for (i = 0; i < rows*cols; i++)
		m->data[i] = 0;

	return m;
}

/* Deletes a matrix.  Returns 0 if successful and -1 if mtx
 * is NULL.
 */
int deleteMatrix(matrix * mtx) {
	if (!mtx) return -1;
	// free mtx's data
	assert (mtx->data);
	free(mtx->data);
	// free mtx itself
	free(mtx);
	return 0;
}

#define ELEM(mtx, row, col) \
  mtx->data[(col-1) * mtx->rows + (row-1)]

/* Copies a matrix.  Returns NULL if mtx is NULL.
 */
matrix * copyMatrix(matrix * mtx) {
	if (!mtx) return NULL;

	// create a new matrix to hold the copy
	matrix * cp = newMatrix(mtx->rows, mtx->cols);

	// copy mtx's data to cp's data
	memcpy(cp->data, mtx->data,
		   mtx->rows * mtx->cols * sizeof(double));

	return cp;
}

/* Sets the (row, col) element of mtx to val.  Returns 0 if
 * successful, -1 if mtx is NULL, and -2 if row or col are
 * outside of the dimensions of mtx.
 */
int setElement(matrix * mtx, int row, int col, __uint8_t val)
{
	if (!mtx) return -1;
	assert (mtx->data);
	if (row <= 0 || row > mtx->rows ||
		col <= 0 || col > mtx->cols)
		return -2;

	ELEM(mtx, row, col) = val;
	return 0;
}

/* Sets the reference val to the value of the (row, col)
 * element of mtx.  Returns 0 if successful, -1 if either
 * mtx or val is NULL, and -2 if row or col are outside of
 * the dimensions of mtx.
 */
int getElement(matrix * mtx, int row, int col,
			   double * val) {
	if (!mtx || !val) return -1;
	assert (mtx->data);
	if (row <= 0 || row > mtx->rows ||
		col <= 0 || col > mtx->cols)
		return -2;

	*val = ELEM(mtx, row, col);
	return 0;
}

/* Sets the reference n to the number of rows of mtx.
 * Returns 0 if successful and -1 if mtx or n is NULL.
 */
int nRows(matrix * mtx, int * n) {
	if (!mtx || !n) return -1;
	*n = mtx->rows;
	return 0;
}

/* Sets the reference n to the number of columns of mtx.
 * Returns 0 if successful and -1 if mtx is NULL.
 */
int nCols(matrix * mtx, int * n) {
	if (!mtx || !n) return -1;
	*n = mtx->rows;
	return 0;
}

/* Prints the matrix to stdout.  Returns 0 if successful
 * and -1 if mtx is NULL.
 */
int printMatrix(matrix * mtx) {
	if (!mtx) return -1;

	int row, col;
	for (row = 1; row <= mtx->rows; row++) {
		for (col = 1; col <= mtx->cols; col++) {
			// Print the floating-point element with
			//  - either a - if negative or a space if positive
			//  - at least 3 spaces before the .
			//  - precision to the hundredths place
			printf("%d ", ELEM(mtx, row, col));
		}
		// separate rows by newlines
		printf("\n");
	}
	return 0;
}

/* Writes the transpose of matrix in into matrix out.
 * Returns 0 if successful, -1 if either in or out is NULL,
 * and -2 if the dimensions of in and out are incompatible.
 */
int transpose(matrix * in, matrix * out) {
	if (!in || !out) return -1;
	if (in->rows != out->cols || in->cols != out->rows)
		return -2;

	int row, col;
	for (row = 1; row <= in->rows; row++)
		for (col = 1; col <= in->cols; col++)
			ELEM(out, col, row) = ELEM(in, row, col);
	return 0;
}

/* Writes the sum of matrices mtx1 and mtx2 into matrix
 * sum. Returns 0 if successful, -1 if any of the matrices
 * are NULL, and -2 if the dimensions of the matrices are
 * incompatible.
 */
int sum(matrix * mtx1, matrix * mtx2, matrix * sum) {
	if (!mtx1 || !mtx2 || !sum) return -1;
	if (mtx1->rows != mtx2->rows ||
		mtx1->rows != sum->rows ||
		mtx1->cols != mtx2->cols ||
		mtx1->cols != sum->cols)
		return -2;

	int row, col;
	for (col = 1; col <= mtx1->cols; col++)
		for (row = 1; row <= mtx1->rows; row++)
			ELEM(sum, row, col) =
					ELEM(mtx1, row, col) + ELEM(mtx2, row, col);
	return 0;
}

/* Writes the product of matrices mtx1 and mtx2 into matrix
 * prod.  Returns 0 if successful, -1 if any of the
 * matrices are NULL, and -2 if the dimensions of the
 * matrices are incompatible.
 */
int product(matrix * mtx1, matrix * mtx2, matrix * prod) {
	if (!mtx1 || !mtx2 || !prod) return -1;
	if (mtx1->cols != mtx2->rows ||
		mtx1->rows != prod->rows ||
		mtx2->cols != prod->cols)
		return -2;

	int row, col, k;
	for (col = 1; col <= mtx2->cols; col++)
		for (row = 1; row <= mtx1->rows; row++) {
			__uint8_t val = 0;
			for (k = 1; k <= mtx1->cols; k++)
				val += ELEM(mtx1, row, k) * ELEM(mtx2, k, col);
			ELEM(prod, row, col) = (uint8_t) modInverse(val);
		}
	return 0;
}

/* Writes the dot product of vectors v1 and v2 into
 * reference prod.  Returns 0 if successful, -1 if any of
 * v1, v2, or prod are NULL, -2 if either matrix is not a
 * vector, and -3 if the vectors are of incompatible
 * dimensions.
 */
int dotProduct(matrix * v1, matrix * v2, double * prod) {
	if (!v1 || !v2 || !prod) return -1;
	if (v1->cols != 1 || v2->cols != 1) return -2;
	if (v1->rows != v2->rows) return -3;

	*prod = 0;
	int i;
	for (i = 1; i <= v1->rows; i++)
		*prod += ELEM(v1, i, 1) * ELEM(v2, i, 1);
	return 0;
}

int identity(matrix * m) {
	if (!m || m->rows != m->cols) return -1;
	int row, col;
	for (col = 1; col <= m->cols; col++)
		for (row = 1; row <= m->rows; row++)
			if (row == col)
				ELEM(m, row, col) = 1;
			else
				ELEM(m, row, col) = 0;
	return 0;
}

int isSquare(matrix * mtx) {
	return mtx && mtx->rows == mtx->cols;
}

int isDiagonal(matrix * mtx) {
	if (!isSquare(mtx)) return 0;
	int row, col;
	for (col = 1; col <= mtx->cols; col++)
		for (row = 1; row <= mtx->rows; row++)
			// if the element is not on the diagonal and not 0
			if (row != col && ELEM(mtx, row, col) != 0)
				// then the matrix is not diagonal
				return 0;
	return 1;
}

int isUpperTriangular(matrix * mtx) {
	if (!isSquare(mtx)) return 0;
	int row, col;
	// looks at positions below the diagonal
	for (col = 1; col <= mtx->cols; col++)
		for (row = col+1; row <= mtx->rows; row++)
			if (ELEM(mtx, row, col) != 0)
				return 0;
	return 1;
}

int diagonal(matrix * v, matrix * mtx) {
	if (!v || !mtx ||
		v->cols > 1 || v->rows != mtx->rows ||
		mtx->cols != mtx->rows)
		return -1;
	int row, col;
	for (col = 1; col <= mtx->cols; col++)
		for (row = 1; row <= mtx->rows; row++)
			if (row == col)
				ELEM(mtx, row, col) = ELEM(v, col, 1);
			else
				ELEM(mtx, row, col) = 0;
	return 0;
}

static void swap(matrix * mtx, int row1, int row2, int col)
{
	for (int i = 0; i < col; i++)
	{
		uint8_t temp = ELEM(mtx,row1,i);
		ELEM(mtx,row1,i) = ELEM(mtx,row2,i);
		ELEM(mtx,row2,i) = temp;
	}
}

int rankOfMatrix(matrix * mtx)
{
	int rank = mtx->cols;
	int R = mtx->rows;

	for (int row = 1; row <= rank; row++) {
        __uint8_t elem = ELEM(mtx,row,row);
        if (elem != 0) {
            for (int col = 1; col <= R; col++) {
                if (col != row) {
                    double mult = (double) ELEM(mtx,col,row) / ELEM(mtx,row,row);
                    for (int i = 1; i <= rank; i++){
                        ELEM(mtx,col,i) -= mult * ELEM(mtx,row,i);
                    }
                }
            }
        } else {
            bool reduce = true;
            for (int i = row + 1; i <= R;  i++) {
                if (ELEM(mtx,i,row)) {
                    swap(mtx, row, i, rank);
                    reduce = false;
                    break ;
                }
            }
            if (reduce) {
                rank--;
                for (int i = 1; i <= R; i ++) {
                    ELEM(mtx, i, row) = ELEM(mtx, i, rank);
                }
            }
            row--;
        }
    }
	return rank;
}

bool invertible(matrix * mtx) {
    int i;
    for(i = 1; i <= mtx->cols; i++){
        if(ELEM(mtx,i,i) == 0) {
            return false;
        }
    }
    return true;
}

void getCofactor(matrix * mat, matrix * temp, int p, int q, int n)
{
    int i = 1, j = 1;

    // Looping for each element of the matrix
    for (int row = 1; row <= n; row++)
    {
        for (int col = 1; col <= n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                ELEM(temp,i,j) = ELEM(mat,row,col);
//                printf("Elemento %d\n", ELEM(temp,i,j));
                j++;
                // Row is filled, so increase row index and
                // reset col index
                if (j == n)
                {
                    j = 1;
                    i++;
                }
            }
        }
    }
}

int determinantOfMatrix(matrix * mat, int n)
{
    int D = 0; // Initialize result

    //  Base case : if matrix contains single element
    if (n == 1)
        return ELEM(mat,1,1);

    matrix * temp = newMatrix(n,n); // To store cofactors

    int sign = 1;  // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 1; f <= n; f++)
    {
        // Getting Cofactor of mat[0][f]
        getCofactor(mat, temp, 0, f, n);
        int aux = sign * ELEM(mat,1,f) * determinantOfMatrix(temp, n - 1);
        D += modInverse(aux);

        // terms are to be added with alternate sign
        sign = -sign;
    }
    printf("D %d\n", D);
    return D;
}

void multiplyByScalar(matrix * mtx, uint8_t scalar){
    int i,j;
    for(i = 1; i <= mtx->rows; i++){
        for(j = 1; j <= mtx->cols; j++){
            ELEM(mtx,i,j) = modInverse(scalar * ELEM(mtx,i,j));
        }
    }
}

matrix * inverse(matrix * mtx){
    matrix * inverse = copyMatrix(mtx);
    uint8_t det = determinantOfMatrix(inverse, inverse->rows);
    multiplyByScalar(inverse, det);
    return inverse;
}



matrix * newMatrixA(int n, int k) {
    int i, j;
    matrix * mtx = newMatrix(n, k);
    setSeed(time(0));
    do {
        for(i = 1; i <= n; i++)
            for(j = 1; j <= k; j++){
            setElement(mtx, i,j, nextChar());
        }
    } while(rankOfMatrix(mtx) != k && invertible(mtx));
    return mtx;
}

//matrix * newMatrixS(matrix * A) {
//    matrix * At;
//    transpose(A, At);
//}
