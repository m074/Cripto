//
// Created by Esteban Kramer on 14/06/2019.
//

#ifndef CRIPTO_MATRIX_H
#define CRIPTO_MATRIX_H

#include <stdbool.h>
#include <stdint.h>


#define ELEM(mtx, row, col) \
  mtx->data[(col-1) * mtx->rows + (row-1)]

typedef struct {
    int rows;
    int cols;
    int32_t * data;
} matrix;

typedef struct {
    int size;
    matrix ** matrixes;
} matrixCol;

matrix * newMatrix(int rows, int cols);

int deleteMatrix(matrix * mtx);

matrix * copyMatrix(matrix * mtx);

int setElement(matrix * mtx, int row, int col, int32_t val);

int getElement(matrix * mtx, int row, int col, int32_t * val);

int nRows(matrix * mtx, int * n);

int nCols(matrix * mtx, int * n);

int printMatrix(matrix * mtx);

int transpose(matrix * in, matrix * out);

int sum(matrix * mtx1, matrix * mtx2, matrix * sum);

int product(matrix * mtx1, matrix * mtx2, matrix * prod);

int dotProduct(matrix * v1, matrix * v2, int32_t * prod);

int identity(matrix * m);

int isSquare(matrix * mtx);

int isDiagonal(matrix * mtx);

int isUpperTriangular(matrix * mtx);

int diagonal(matrix * v, matrix * mtx);

int rankOfMatrix(matrix * mtx);

matrix * newMatrixA(int n, int k);

bool invertible(matrix * mtx);

matrix * inverse(matrix * mtx);

int64_t determinant(matrix * a);

matrix * newMatrixS(matrix * a);

matrix * newMatrixR(matrix * s, matrix * sCalculated);

matrixCol* getVectorsX(int size, int quantity);

matrixCol* getVectorsV(matrix* ma, matrixCol* xv);

void normalize(matrix* m);

matrixCol * generateAllMatrixG(int size, int32_t * c, matrix * r);

matrixCol * newMatrixCol(int size);

matrix* newMatrixB(matrixCol* mc, int k);

matrix * subMatrix(matrix * m, int col);

matrix * getrsmall(matrixCol * allG, __uint8_t * c, int x, int y);

matrix * solveEquations(matrix * m, matrix * g);

matrix* recoverMatrixR(matrixCol* allG, uint8_t * c);

matrix * newMatrixRW(matrix * w, matrix * doubleS);

matrix * newMatrixSh(matrix * v, matrix * g);

matrix * newSecretMatrixS(matrix * doubleS, matrix * r);

matrixCol* getMatrixColSh(matrixCol* v,matrixCol* g);

matrixCol* getMatrixColG(matrixCol* mcol_shadows, int k);

int matrix_add(matrix * mtx1, matrix * mtx2, matrix * substract);

matrix* recoverMatrixS(matrix* mdobles, matrix* mr);

void deleteMatrixCol(matrixCol* mc);

matrix * generateRandomMatrix(int rows, int cols);

void rankOfMatrix2(matrix * mtx, int rank);

#endif //CRIPTO_MATRIX_H
