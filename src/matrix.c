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
#include <math.h>

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
	m->data = (int32_t *) malloc((rows)*(cols)*sizeof(int32_t));
	// set all data to 0
	int i;
	for (i = 0; i < rows*cols; i++)
		m->data[i] = 0;

	return m;
}

/* Creates a ``rows by cols'' matrix with all values 0.
 * Returns NULL if rows <= 0 or cols <= 0 and otherwise a
 * pointer to the new matrix.
 */
matrixCol * newMatrixCol(int size) {
    if (size <= 0) return NULL;

    // allocate a matrix structure
    matrixCol * mC = (matrixCol *) malloc(sizeof(matrixCol));

    // set dimensions
    mC->size = size;

    // allocate a double array of length rows * cols
    mC->matrixes = (matrix **) malloc(size * sizeof(matrix *) );

    return mC;
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

void deleteMatrixCol(matrixCol* mc){
    for(int i=0; i<mc->size; i++){
        deleteMatrix(mc->matrixes[i]);
    }
    free(mc->matrixes);
    free(mc);
}


#define ELEMFROMARRAY(mtx, row, col, dim) \
  mtx[(col) * dim + (row)]


/* Copies a matrix.  Returns NULL if mtx is NULL.
 */
matrix * copyMatrix(matrix * mtx) {
	if (!mtx) return NULL;

	// create a new matrix to hold the copy
	matrix * cp = newMatrix(mtx->rows, mtx->cols);

	// copy mtx's data to cp's data
	memcpy(cp->data, mtx->data,
		   mtx->rows * mtx->cols * sizeof(int32_t));

	return cp;
}

/* Sets the (row, col) element of mtx to val.  Returns 0 if
 * successful, -1 if mtx is NULL, and -2 if row or col are
 * outside of the dimensions of mtx.
 */
int setElement(matrix * mtx, int row, int col, int32_t val)
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
int getElement(matrix * mtx, int row, int col, int32_t * val) {
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
    printf("\n");
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

/* Writes the substraction of matrices mtx1 and mtx2 into matrix
 * sum. Returns 0 if successful, -1 if any of the matrices
 * are NULL, and -2 if the dimensions of the matrices are
 * incompatible.
 */
int substract(matrix * mtx1, matrix * mtx2, matrix * substract) {
    if (!mtx1 || !mtx2 || !substract) return -1;
    if (mtx1->rows != mtx2->rows ||
        mtx1->rows != substract->rows ||
        mtx1->cols != mtx2->cols ||
        mtx1->cols != substract->cols)
        return -2;

    int row, col;
    for (col = 1; col <= mtx1->cols; col++)
        for (row = 1; row <= mtx1->rows; row++)
            ELEM(substract, row, col) =
                    ELEM(mtx1, row, col) - ELEM(mtx2, row, col);
    return 0;
}


int matrix_add(matrix * mtx1, matrix * mtx2, matrix * substract) {
    if (!mtx1 || !mtx2 || !substract) return -1;
    if (mtx1->rows != mtx2->rows ||
        mtx1->rows != substract->rows ||
        mtx1->cols != mtx2->cols ||
        mtx1->cols != substract->cols)
        return -2;

    int row, col;
    for (col = 1; col <= mtx1->cols; col++)
        for (row = 1; row <= mtx1->rows; row++)
            ELEM(substract, row, col) =
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
            int32_t val = 0;
			for (k = 1; k <= mtx1->cols; k++)
				val += ELEM(mtx1, row, k) * ELEM(mtx2, k, col);
			ELEM(prod, row, col) = val;
		}
	return 0;
}

/* Writes the dot product of vectors v1 and v2 into
 * reference prod.  Returns 0 if successful, -1 if any of
 * v1, v2, or prod are NULL, -2 if either matrix is not a
 * vector, and -3 if the vectors are of incompatible
 * dimensions.
 */
int dotProduct(matrix * v1, matrix * v2, int32_t * prod) {
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
	for (int i = 1; i <= col; i++)
	{
        int32_t temp = ELEM(mtx,row1,i);
		ELEM(mtx,row1,i) = ELEM(mtx,row2,i);
		ELEM(mtx,row2,i) = temp;
	}
}

int rankOfMatrix(matrix * mtx)
{
	int rank = mtx->cols;
	int R = mtx->rows;

	for (int row = 1; row <= rank && row <= R; row++) {
        int32_t elem = ELEM(mtx,row,row);
        if (elem != 0) {
            for (int col = 1; col <= R; col++) {
                if (col != row) {
                    for (int i = 1; i <= rank; i++){
                        ELEM(mtx,col,i) -= ELEM(mtx,row,i);
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

void multiplyByScalar(matrix * mtx, int32_t scalar){
    int i,j;
    for(i = 1; i <= mtx->rows; i++){
        for(j = 1; j <= mtx->cols; j++){
            int32_t elem = scalar * ELEM(mtx,i,j);
            ELEM(mtx,i,j) = elem;
        }
    }
}

matrix * newMatrixA(int n, int k) {
    int i, j;
    matrix * mtx = newMatrix(n, k);
    matrix * prod = NULL;
    setSeed(time(0));
    do {
        if(prod!=NULL){
            deleteMatrix(prod);
        }

        for(i = 1; i <= n; i++)
            for(j = 1; j <= k; j++){
            setElement(mtx, i,j, nextChar());
        }
        matrix * mtxTransposed = newMatrix(k,n);
        prod = newMatrix(n,n);
        transpose(mtx,mtxTransposed);
        product(mtx,mtxTransposed,prod);
        deleteMatrix(mtxTransposed);

    } while(rankOfMatrix(mtx) != k && invertible(prod));
    normalize(mtx);
    deleteMatrix(prod);
    return mtx;
}

void normalize(matrix * m){
    int i,j;
    for(i = 1; i <= m->rows; i++)
        for(j = 1; j <= m->cols; j++){
            while(ELEM(m,i,j) < 0){
                ELEM(m, i, j) = ELEM(m,i,j) + 251;
            }
            ELEM(m,i,j) = ELEM(m,i,j) % 251;
        }
}

int32_t determinant(matrix * a) {
    int det = 0 ;                   // init determinant
    // square array
    int n = a->rows;

    if (n < 1)    {   }                // error condition, should never get here

    else if (n == 1) {                 // should not get here
        det = ELEM(a,1,1);
    }

    else if (n == 2)  {                // basic 2X2 sub-matrix determinate
        // definition. When n==2, this ends the
        int d1 = ELEM(a,1,1);
        int d2 = ELEM(a,2,2);
        int d3 = ELEM(a,2,1);
        int d4 = ELEM(a,1,2);
        det = d1 * d2 - d3 * d4 ;// the recursion series
    }


        // recursion continues, solve next sub-matrix
    else {                             // solve the next minor by building a
        matrix * aux = newMatrix(n-1, n-1);
        int i, i2, j2, rows, cols;
        int sign = 1;
        rows = cols = 1;
        for(i = 1; i <= a->rows; i++) {
            for(i2 = 1; i2 <= a->rows; i2++) {
                for(j2= 2; j2 <= a->cols; j2++) {
                    if(i != i2 ) {
                        setElement(aux, rows, cols, ELEM(a,i2,j2));
                        cols++;
                    }
                }
                if(i != i2){
                    cols = 1;
                    rows++;
                }
            }
            rows = 1;
            det += sign * ELEM(a,i,1) * determinant(aux);
            sign = -sign;
        }
    }
    return(det);
}

matrix * inverse(matrix * a) {
    matrix * ans = newMatrix(a->rows, a->cols);
    matrix * subMatrix = newMatrix(a->rows-1, a->cols-1);
    int i,j, i2, j2, cols, rows, sign;
    cols = rows = 1;
    for(i = 1; i <= a->rows; i++)
        for(j = 1; j <= a->cols; j++){
            for(i2 = 1; i2 <= a->rows; i2++) {
                for(j2= 1; j2 <= a->cols; j2++) {
                    if(i != i2 && j != j2 ) {
                        setElement(subMatrix, rows, cols, ELEM(a,i2,j2));
                        cols++;
                    }
                }
                if(i != i2){
                    cols = 1;
                    rows++;
                }
            }
            rows = 1;
            sign = (i + j) % 2 == 0 ? 1 : -1;
            setElement(ans, i,j, sign * determinant(subMatrix));
    }
    matrix * t = newMatrix(a->rows, a->cols);
    transpose(ans, t);
    int32_t scalar = determinant(a);
    if(scalar > 251 || scalar < 0){
        scalar = multiplicativeInverse(scalar);
    }
    multiplyByScalar(t, scalar);
    normalize(t);

    deleteMatrix(ans);
    deleteMatrix(subMatrix);

    return t;
}

matrix * newMatrixS(matrix * a) {
    //Define aux matrices
    matrix * at, * ata, *ataInv, * aataInv, * aataInvat;
    at = newMatrix(a->cols, a->rows);
    transpose(a, at);
    ata = newMatrix(at->rows, a->cols);
    product(at, a, ata);
    ataInv = inverse(ata);

    aataInv = newMatrix(a->rows, ataInv->cols);
    product(a, ataInv, aataInv);

    aataInvat = newMatrix(aataInv->rows, at->cols);
    product(aataInv, at, aataInvat);

    deleteMatrix(at);
    deleteMatrix(ata);
    deleteMatrix(ataInv);
    deleteMatrix(aataInv);

    normalize(aataInvat);

    return aataInvat;
}

matrix * newMatrixR(matrix * s, matrix * sCalculated) {
    matrix * r = newMatrix(s->rows, s->cols);
    substract(s,sCalculated, r);
    normalize(r);
    return r;
}

matrix* recoverMatrixS(matrix* mdobles, matrix* mr){
    matrix* ms = newMatrix(mdobles->rows, mdobles->cols);
    matrix_add(mdobles,mr,ms);
    normalize(ms);
    return ms;
}




matrixCol* getVectorsX(int size, int quantity){
    matrixCol *mc=newMatrixCol(quantity);
    matrix* m = newMatrixA(quantity,size);
    for(int r=0;r<quantity;r++){
//        mc->matrixes[r]=malloc(sizeof(matrix*));
        mc->matrixes[r]=newMatrix(size,1);
        for(int j=1;j<=size;j++){
            ELEM(mc->matrixes[r],j,1)=ELEM(m,r+1,j);
        }
    }
    deleteMatrix(m);
    return mc;
}

matrixCol* getVectorsV(matrix* ma, matrixCol* xv){
    matrixCol *mc=newMatrixCol(xv->size);
    for(int r=0;r<xv->size;r++){
//        mc->matrixes[r]=malloc(sizeof(matrix*));
        mc->matrixes[r]=newMatrix(ma->rows,1);
        product(ma,xv->matrixes[r],mc->matrixes[r]);
        normalize(mc->matrixes[r]);

    }

    return mc;
}

matrix * newMatrixG(matrix * r, int32_t c){
    int i;
    matrix * g = newMatrix(r->rows, 2);
    for(i = 1; i <= g->rows; i++) {
        if(r->cols == 4){
            ELEM(g, i, 1) = ELEM(r,i,1) + ELEM(r, i, 2) * c;
            ELEM(g, i, 2) = ELEM(r,i,3) + ELEM(r, i, 4) * c;
        } else {
            ELEM(g, i, 1) = ELEM(r,i,1) + ELEM(r, i, 2) * c + ELEM(r,i,3) * c * c + ELEM(r, i, 4) * c * c * c;
            ELEM(g, i, 2) = ELEM(r,i,5) + ELEM(r, i, 6) * c + ELEM(r,i,7) * c * c + ELEM(r, i, 8) * c * c * c;
        }
    }
    return g;
}

matrixCol * generateAllMatrixG(int size, int32_t * c, matrix * r) {
    int i;
    matrixCol * mc = newMatrixCol(size);
    for(i = 0; i < size; i++){
        mc->matrixes[i] = newMatrixG(r, c[i]);
    }
    return mc;
}


matrix* newMatrixB(matrixCol* mc){
    matrix * b = newMatrix(mc->matrixes[0]->rows, 2);

    for(int i = 1; i <= mc->matrixes[0]->rows; i++){
        for(int j = 0; j<mc->size;j++){
            setElement(b, i, 1, ELEM(mc->matrixes[j], i,1));
        }
    }
    return b;
}



/*Generates a new submatrix excluding the
 * col from the matrix passed as
 * arguments*/
matrix * subMatrix(matrix * m, int col) {
    int i, j, i2, j2;
    i2 = j2 = 1;
    matrix * subMatrix = newMatrix(m->rows, m->cols - 1);

    if(!m || col <= 0){
        return NULL;
    }

    for(i = 1; i <= m->rows; i++) {
        for(j = 1; j <=m->cols; j++) {
            if(j != col) {
                setElement(subMatrix, i2,j2, ELEM(m,i,j));
                j2++;
            }
        }
        j2 = 1;
        i2++;
    }

    return subMatrix;
}


matrix* recoverMatrixR(matrixCol* allG, int32_t* c){
    matrix * mr = newMatrix(allG->matrixes[0]->rows,allG->matrixes[0]->rows);
    for(int i=1;i<=mr->rows;i++){
        for(int j=1;j<=2;j++){
            matrix * rsmall = getrsmall(allG,c,i,j);
            for(int k=1; k<=(rsmall->rows/2);k++){
                ELEM(mr,i,(rsmall->rows/2)*(j-1)+k)= ELEM(rsmall,k,1);
            }
            deleteMatrix(rsmall);
        }
    }
    normalize(mr);
    return mr;
}


matrix * getrsmall(matrixCol * allG, int32_t * c, int x, int y) {
    int i;
    matrix * cMatrix = newMatrix(allG->size, allG->size);
    matrix * g = newMatrix(allG->size, 1);

    for(i = 1; i <= allG->size; i++){
        setElement(g, i, 1, ELEM(allG->matrixes[i-1],x, y));

        setElement(cMatrix, i, 1, 1);
        setElement(cMatrix, i, 2, c[i-1]);
        if(allG->size == 4) {
            setElement(cMatrix, i, 3, c[i-1] * c[i-1]);
            setElement(cMatrix, i, 4, c[i-1] * c[i-1] * c[i-1]);
        }
    }

//    printMatrix(cMatrix);
//    printf("\n");
//    printMatrix(g);
//    printf("\nx: %d, y:%d\n", x, y);
    matrix* rot= solveEquations(cMatrix, g);
    deleteMatrix(cMatrix);
    deleteMatrix(g);
    return rot;
}

matrix * solveEquations(matrix * m, matrix * g) {
    int i, count;
    matrix * results = newMatrix(m->rows, 1);


    int det = determinant(m);
    for(count = 1; count <= m->cols; count++) {
        matrix * copy = copyMatrix(m);
        for(i = 1; i <= m->rows; i++){
            ELEM(copy, count, i) = ELEM(g,i,1);
        }
        int dx = determinant(copy);
        deleteMatrix(copy);
        ELEM(results,count,1)=dx/det;
    }

    return results;
}

matrix * newMatrixRW(matrix * w, matrix * doubleS) {
    matrix * results = newMatrix(w->rows, w->cols);
    substract(w, doubleS, results);
    normalize(results);
    return results;
}

matrix * newMatrixSh(matrix * v, matrix * g) {
    int i, j;
    matrix * results = newMatrix(g->rows, g->cols + 1);
    for(i = 1; i <= results->rows; i++) {
        ELEM(results, i, 1) = ELEM(v, i, 1);
        for(j = 2; j <= results->cols; j++) {
            ELEM(results,i,j) = ELEM(g, i, j - 1);
        }
    }
    normalize(results);
    return results;
}

matrix * newSecretMatrixS(matrix * doubleS, matrix * r) {
    matrix * results = newMatrix(doubleS->rows, doubleS->cols);
    substract(doubleS, r, results);
    normalize(results);
    return results;
}


matrixCol* getMatrixColSh(matrixCol* v,matrixCol* g){
    matrixCol* mcs=newMatrixCol(g->size);
    for(int i=0;i<g->size;i++){
        mcs->matrixes[i]=newMatrixSh(v->matrixes[i],g->matrixes[i]);
    }

    return mcs;

}

matrix* recoverG(matrix* m_shadow){
    matrix* mg=newMatrix(m_shadow->rows,m_shadow->cols-1);
    for(int i=1;i<=m_shadow->rows;i++){
        for(int j=2;j<=m_shadow->cols;j++){
            setElement(mg,i,j-1,ELEM(m_shadow,i,j));
        }
    }
    return mg;
}

matrixCol* getMatrixColG(matrixCol* mcol_shadows){
    matrixCol* mcg = newMatrixCol(mcol_shadows->size);
    for(int i=0;i<mcol_shadows->size;i++){
        mcg->matrixes[i] = recoverG(mcol_shadows->matrixes[i]);
    }
    return mcg;
}

matrix * generateRandomMatrix(int rows, int cols) {
    int i,j;
    matrix * result = newMatrix(rows, cols);

    for(i = 1; i <= rows; i++)
        for(j = 1; j <= cols; j++)
            setElement(result, i, j, nextChar());
    return result;
}




