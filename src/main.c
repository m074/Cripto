#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "general.h"
#include "matrix.h"
#include "utilities.h"
#include "random.h"


int main(int argc, char *argv[]){
    setSeed(time(0));

    parse_options(argc,argv);
//
//
//    int cs[8] = {1, 2, 3, 4, 5, 6, 7, 8};
//    int n = 8;
//    int k = n/2 ;
//    matrix *ma = newMatrixA(n, k);
//    matrix *mdoubles = newMatrixS(ma);
//
//    matrix *ms = generateRandomMatrix(n, n);
//    normalize(ms);
//    setElement(ms, 1, 1, 200);
//    setElement(ms, 2, 1, 200);
//    setElement(ms, 3, 1, 200);
//
//    setElement(ms, 1, 2, 241);
//    matrix *mw = generateRandomMatrix(n, n);
//
//    setElement(mw, 3, 3, 13);
//
//    matrix *mr = newMatrixR(ms, mdoubles);
//
//
//    matrixCol *mcg = generateAllMatrixG(n, cs, mr);
//
//    matrixCol *vectorsX = getVectorsX(k, n);
//    matrixCol *vectorsV = getVectorsV(ma, vectorsX);
//    matrixCol *shadows = getMatrixColSh(vectorsV, mcg);
//
//    //desencripcion
//
//
//    matrix *mb = newMatrixB(shadows,k);
//    matrix *mdobleS = newMatrixS(mb);
//
//    matrixCol *mcg2 = getMatrixColG(shadows, k);
//
//
//    matrix *new_mr = recoverMatrixR(mcg2, cs);
//
//
//    matrix *new_ms = recoverMatrixS(mdobleS, mr);
//
//    printf("Matrix a\n");
//    printMatrix(ma);
//
//    for(int gg=0;gg<vectorsV->size;gg++){
//        printf("xx\n");
//        printMatrix(vectorsX->matrixes[gg]);
//
//    }
//
//    for(int gg=0;gg<vectorsV->size;gg++){
//        printf("vv\n");
//        printMatrix(vectorsV->matrixes[gg]);
//
//    }
//
//
//
//
//
//
//    matrix* a=ma;
//    matrix * at, * ata;
//
//
//    int c=0;
//    do{
//        c+=1;
//      ma = newMatrixA(n, k);
//       mdoubles = newMatrixS(ma);
//
//      ms = generateRandomMatrix(n, n);
//        normalize(ms);
//        setElement(ms, 1, 1, 200);
//        setElement(ms, 2, 1, 200);
//        setElement(ms, 3, 1, 200);
//
//        setElement(ms, 1, 2, 241);
//mw = generateRandomMatrix(n, n);
//
//        setElement(mw, 3, 3, 13);
//
//mr = newMatrixR(ms, mdoubles);
//
//mcg = generateAllMatrixG(n, cs, mr);
//
//vectorsX = getVectorsX(k, n);
//vectorsV = getVectorsV(ma, vectorsX);
//shadows = getMatrixColSh(vectorsV, mcg);
//
//        //desencripcion
//
//
//mb = newMatrixB(shadows,k);
//mdobleS = newMatrixS(mb);
//
//mcg2 = getMatrixColG(shadows, k);
//
//
//new_mr = recoverMatrixR(mcg2, cs);
//
//
//new_ms = recoverMatrixS(mdobleS, mr);
//
//        printf("Matrix a\n");
//        printMatrix(ma);
//
//        for(int gg=0;gg<vectorsV->size;gg++){
//            printf("xx\n");
//            printMatrix(vectorsX->matrixes[gg]);
//
//        }
//
//        for(int gg=0;gg<vectorsV->size;gg++){
//            printf("vv\n");
//            printMatrix(vectorsV->matrixes[gg]);
//
//        }
//
//
//
//
//    }while(ELEM(ms,1,1)==ELEM(new_ms,1,1));
//
//
//    printf("Matrix b\n");
//    printMatrix(mb);
//
//
//
//    printf("Matrix origianl S\n");
//    printMatrix(ms);
//
//
//    printf("Matrix nueva S\n");
//    printMatrix(new_ms);
//
//
//    printf("Matrix origianl sS\n");
//    printMatrix(mdoubles);
//
//
//    printf("Matrix nueva Ss\n");
//    printMatrix(mdobleS);
//
//    printf("Matrix origianl r\n");
//    printMatrix(mr);
//
//
//    printf("Matrix nueva rr\n");
//    printMatrix(new_mr);
//
//    a=ma;
//
//    at = newMatrix(a->cols, a->rows);
//    transpose(a, at);
//    ata = newMatrix(at->rows, a->cols);
//    product(at, a, ata);
//
//    printf("Matrix ata\n");
//    printMatrix(ata);
//    printf("deter %d\n",determinant(ata)%251);
//
//    printf("Veces que fallo: %d\n",c);
//    if(new_mr==NULL){new_mr=NULL;};
//    exit(EXIT_SUCCESS);
}

