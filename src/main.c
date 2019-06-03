#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"

int main(int argc, char *argv[]){
    Configuration* cfg = parse_options(argc,argv);
    printf("m_image: %s\n",cfg->m_image_name);

    Bmp* bmp = read_bmp("Marca.bmp");

    printf("%d %d \n", bmp->height, bmp->width);

    exit(EXIT_SUCCESS);
}

