//
// Created by Esteban Kramer on 14/06/2019.
//

#ifndef CRIPTO_MATRIX_H
#define CRIPTO_MATRIX_H

#include <stdbool.h>


typedef struct {
    int rows;
    int cols;
    __uint8_t * data;
} matrix;

matrix * newMatrix(int rows, int cols);

int deleteMatrix(matrix * mtx);

matrix * copyMatrix(matrix * mtx);

int setElement(matrix * mtx, int row, int col, __uint8_t val);

int getElement(matrix * mtx, int row, int col, double * val);

int nRows(matrix * mtx, int * n);

int nCols(matrix * mtx, int * n);

int printMatrix(matrix * mtx);

int transpose(matrix * in, matrix * out);

int sum(matrix * mtx1, matrix * mtx2, matrix * sum);

int product(matrix * mtx1, matrix * mtx2, matrix * prod);

int dotProduct(matrix * v1, matrix * v2, double * prod);

int identity(matrix * m);

int isSquare(matrix * mtx);

int isDiagonal(matrix * mtx);

int isUpperTriangular(matrix * mtx);

int diagonal(matrix * v, matrix * mtx);

int rankOfMatrix(matrix * mtx);

matrix * newMatrixA(int n, int k);

bool invertible(matrix * mtx);

matrix * inverse(matrix * mtx);

int determinantOfMatrix(matrix * mat, int n);

matrix * inverse(matrix * mtx);

#endif //CRIPTO_MATRIX_H