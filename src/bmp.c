#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "general.h"



Bmp* read_bmp(char* filename){

    Bmp* bmp= malloc(sizeof(Bmp));
    bmp->bb=readfile(filename);

    u_int32_t width;
    u_int32_t height;
    u_int16_t bits_per_pixel;
    u_int32_t compression;
    u_int32_t offset;

    memcpy(&width, bmp->bb->p + WIDTH_HEADER_OFFSET, WIDTH_HEADER_SIZE);
    memcpy(&height, bmp->bb->p + HEIGHT_HEADER_OFFSET, HEIGHT_HEADER_SIZE);
    memcpy(&bits_per_pixel, bmp->bb->p + BITS_PER_PIXEL_HEADER_OFFSET, BITS_PER_PIXEL_HEADER_SIZE);
    memcpy(&compression, bmp->bb->p + COMPRESSION_HEADER_OFFSET, COMPRESSION_HEADER_SIZE); //TODO sacar?
    memcpy(&offset, bmp->bb->p + BODY_START_HEADER_OFFSET, BODY_START_HEADER_SIZE);

    bmp->width = width;
    bmp->height = height;
    bmp->bits = bits_per_pixel;
    bmp->offset = offset;

    return bmp;
}


void write_bmp(Bmp* bmp){
    //TODOAA
}
