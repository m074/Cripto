#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "general.h"
#include "matrix.h"


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

u_int8_t get_byte(Img* img,u_int32_t pos){
    u_int8_t s;
    s = *(img->bb->p + img->offset + pos);
    return s;
}

void set_byte(Img* img,u_int32_t pos, u_int8_t value){
    memcpy((img->bb->p + img->offset + pos) , &value, sizeof(u_int8_t));
}

void set_bits(Img* img,u_int32_t pos, u_int8_t value, int bits){ //TODO check
    u_int8_t c = get_byte(img,pos);

    if(bits==1){
        value = value << 7;
        value = value >> 7;
        c = c >> 1;
        c = c << 1;
        c = c | value;

    }
    if(bits==2){
        value = value << 6;
        value = value >> 6;
        c = c >> 2;
        c = c << 2;
        c = c | value;

    }
    set_byte(img,pos,c);

}

u_int8_t get_bits(Img* img,u_int32_t pos, int bits){
    u_int8_t c = get_byte(img,pos);
    printf("%d\n",c);
    if(bits==1){
        c = c & 1;
    }
    if(bits==2){
        c = c & 3;
    }
    return c;
}

matrix* getSmatrix(Img* img, int number,int size){
    matrix* m = newMatrix(size,size);
    __uint8_t* pos = img->bb->p + img->offset + (number*size*size);
    for(int j=1; j<=size; j++){
        for(int i=1; i<=size; i++){
            setElement(m,i,j,*pos);
            pos+=1;
        }
    }
    return m;
}


Img** read_images_from_dir(char * directory, int n) {
    int image_qty = 0;
    struct dirent *p_dirent;
    DIR* dir;
    dir = opendir(directory);
    Img** images = malloc(8 * sizeof(Img*)); //TODO magic number
    char * path;

    //assure(dir != NULL, "Problem opening directory, check your sintax.\n");
    while ((p_dirent = readdir(dir)) != NULL) {
        if(strstr(p_dirent->d_name, ".bmp") && image_qty < 8 && image_qty <= n) { //TODO magic number
            path = calloc(strlen(directory) + strlen(p_dirent->d_name) + 2, 1);
            strcpy(path, directory);
            strcat(path, "/");
            strcat(path, p_dirent->d_name);

            // images[image_qty] = malloc(sizeof(image_t));
            images[image_qty++] = read_bmp(path);
            free(path);
        }
    }
    closedir(dir);

    return images;
}