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
    matrix* a=newMatrixA(4,2);
    setElement(a,1,1,3);
    setElement(a,1,2,7);

    setElement(a,2,1,6);
    setElement(a,2,2,1);

    setElement(a,3,1,2);
    setElement(a,3,2,5);

    setElement(a,4,1,6);
    setElement(a,4,2,6);

    matrix * letS = newMatrix(4,4);
    setElement(letS,1,1,2);
    setElement(letS,1,2,5);
    setElement(letS,1,3,2);
    setElement(letS,1,4,3);

    setElement(letS,2,1,3);
    setElement(letS,2,2,6);
    setElement(letS,2,3,4);
    setElement(letS,2,4,5);

    setElement(letS,3,1,4);
    setElement(letS,3,2,7);
    setElement(letS,3,3,4);
    setElement(letS,3,4,6);

    setElement(letS,4,1,1);
    setElement(letS,4,2,4);
    setElement(letS,4,3,1);
    setElement(letS,4,4,7);

    matrix * s = newMatrixS(a);
    matrix * r = newMatrixR(letS, s);
    printMatrix(r);

    exit(EXIT_SUCCESS);
}

