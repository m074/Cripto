#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "matrix.h"
#include "utilities.h"
#include <math.h>

//
//int main(int argc, char *argv[]){
//    Configuration* cfg = parse_options(argc,argv);
////    printf("m_image: %s\n",cfg->m_image_name);
//    cfg->d_mode=1;
//
//    Img* bmp = read_bmp("Marca.bmp");
//
//    int a=writefile(bmp->bb,"lala.bmp");
//    printf("%d",a);
//
//    printf("%d %d \n", bmp->height, bmp->width);
//    matrix* m =getSmatrix(bmp,0,4);
//    set_bits(bmp,0,2,2);
//    int asda=get_bits(bmp,0,2);
//    printMatrix(m);
//
//    printf("%d \n",asda);
//
//    exit(EXIT_SUCCESS);
//}

int main(int argc, char *argv[]){
    parse_options(argc,argv);
//    matrix* sh1=newMatrixA(4,3);
//    setElement(sh1,1,1,62);
//    setElement(sh1,1,2,36);
//    setElement(sh1,1,3,92);
//
//    setElement(sh1,2,1,59);
//    setElement(sh1,2,2,101);
//    setElement(sh1,2,3,58);
//
//    setElement(sh1,3,1,43);
//    setElement(sh1,3,2,126);
//    setElement(sh1,3,3,142);
//
//    setElement(sh1,4,1,84);
//    setElement(sh1,4,2,26);
//    setElement(sh1,41,3,163);
//
//    matrix* sh2=newMatrixA(4,3);
//    setElement(sh2,1,1,40);
//    setElement(sh2,1,2,71);
//    setElement(sh2,1,3,132);
//
//    setElement(sh2,2,1,28);
//    setElement(sh2,2,2,169);
//    setElement(sh2,2,3,47);
//
//    setElement(sh2,3,1,28);
//    setElement(sh2,3,2,198);
//    setElement(sh2,3,3,72);
//
//    setElement(sh2,4,1,48);
//    setElement(sh2,4,2,14);
//    setElement(sh2,41,3,150);
//
//    printMatrix(sh1);
//    printf("\n");
//    printMatrix(sh2);
//    printf("\n");
//    matrix * b = newMatrixB(sh1,sh2);
//    printMatrix(b);
//    printf("\n");
//    printMatrix(newMatrixS(b));
//    printf("PRINTING G1\n");
//    matrix * G1 = subMatrix(sh1, 1);
//    printMatrix(G1);
//    printf("\n");
//    matrix * G2 = subMatrix(sh2, 1);
//    printMatrix(G2);
//    printf("\n");
//
//    int32_t c[2] = {1,2};
//    matrixCol * mCol = newMatrixCol(2);
//    mCol->matrixes[0] = G1;
//    mCol->matrixes[1] = G2;
//
//    printMatrix(recoverMatrixR(mCol, c));
//
//
//    exit(EXIT_SUCCESS);
}

