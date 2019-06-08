#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "general.h"



Img* read_bmp(char* filename){

    Img* img= malloc(sizeof(Img));
    img->bb=readfile(filename);

    u_int32_t width;
    u_int32_t height;
    u_int16_t bits_per_pixel;
    u_int32_t compression;
    u_int32_t offset;

    memcpy(&width, img->bb->p + WIDTH_HEADER_OFFSET, WIDTH_HEADER_SIZE);
    memcpy(&height, img->bb->p + HEIGHT_HEADER_OFFSET, HEIGHT_HEADER_SIZE);
    memcpy(&bits_per_pixel, img->bb->p + BITS_PER_PIXEL_HEADER_OFFSET, BITS_PER_PIXEL_HEADER_SIZE);
    memcpy(&compression, img->bb->p + COMPRESSION_HEADER_OFFSET, COMPRESSION_HEADER_SIZE); //TODO sacar?
    memcpy(&offset, img->bb->p + BODY_START_HEADER_OFFSET, BODY_START_HEADER_SIZE);

    img->width = width;
    img->height = height;
    img->bits = bits_per_pixel;
    img->offset = offset;

    return img;
}

Img* copy_img(Img* img){
    Img* img2 = malloc(sizeof(Img));
    memcpy(img2,img,sizeof(Img));
    img2->bb = copy_bbuffer(img->bb);

    return img2;
}

void free_img(Img* img){
    free_bbuffer(img->bb);
    free(img);
}


void write_bmp(Img* bmp){
    //TODOAA
}
