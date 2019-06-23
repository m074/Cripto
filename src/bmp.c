#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "general.h"
#include "matrix.h"


Img* read_bmp(char* filename){

    Img* img= malloc(sizeof(Img));

    img->filename=malloc(sizeof(char)*(1+strlen(filename)));
    strcpy(img->filename,filename);

    img->bb=readfile(filename);


    u_int32_t width;
    u_int32_t height;
    u_int16_t bits_per_pixel;
    u_int32_t compression;
    u_int32_t offset;
    u_int8_t c;

    memcpy(&width, img->bb->p + WIDTH_HEADER_OFFSET, WIDTH_HEADER_SIZE);
    memcpy(&height, img->bb->p + HEIGHT_HEADER_OFFSET, HEIGHT_HEADER_SIZE);
    memcpy(&bits_per_pixel, img->bb->p + BITS_PER_PIXEL_HEADER_OFFSET, BITS_PER_PIXEL_HEADER_SIZE);
    memcpy(&compression, img->bb->p + COMPRESSION_HEADER_OFFSET, COMPRESSION_HEADER_SIZE);
    memcpy(&offset, img->bb->p + BODY_START_HEADER_OFFSET, BODY_START_HEADER_SIZE);

    memcpy(&c, img->bb->p + 6, 1);
    printf("--------c===%d-----\n",c);
    img->width = width;
    img->height = height;
    img->bits = bits_per_pixel;
    img->offset = offset;
    img->c = c+1;

    return img;
}

void set_c(Img* img, u_int8_t c){
    img->c = c;
    memcpy(img->bb->p + 6,&c, 1);
}

void change_filename(Img* img,char* filename){
    free(img->filename);
    img->filename=malloc(sizeof(char)*(1+strlen(filename)));
    strcpy(img->filename,filename);

}

Img* copy_img(Img* img){
    Img* img2 = malloc(sizeof(Img));
    memcpy(img2,img,sizeof(Img));
    img2->bb = copy_bbuffer(img->bb);
    img2->filename = malloc(sizeof(char)*(strlen(img2->filename)+1));
    strcpy(img2->filename,img->filename);


    return img2;
}

void deleteImg(Img* img){
    free_bbuffer(img->bb);
    free(img->filename);
    free(img);
}

u_int8_t get_byte(Img* img,u_int32_t pos){
    u_int8_t s;
    s =  img->bb->p[img->offset + pos];
    return s;
}

void set_byte(Img* img,u_int32_t pos, u_int8_t value){
    img->bb->p[img->offset + pos]=value;
}

void set_bits(Img* img,u_int32_t pos, u_int8_t value, int bits){
    u_int8_t c = get_byte(img,pos);
    if(bits==1){
        value = value >> 7;
        c = c >> 1;
        c = c << 1;
        c = c | value;

    }
    if(bits==2){

        value = value >>6;
        c = c >> 2;
        c = c << 2;

        c = c | value;


    }
    set_byte(img,pos,c);
}

u_int8_t get_bits(Img* img,u_int32_t pos, int bits){
    u_int8_t c = get_byte(img,pos);

    if(bits==1){
        c = c & 0x1;
    }
    if(bits==2){
        c = c & 0x3;
    }
    return c;
}


void reduceto251(matrix * m){
    int i,j;
    for(i = 1; i <= m->rows; i++)
        for(j = 1; j <= m->cols; j++){
            if(ELEM(m,i,j) >=250 ){
                ELEM(m, i, j) = 250;
            }
            if(ELEM(m,i,j) == 0 ){
                ELEM(m, i, j) = 1;
            }
        }
}


matrix* getMatrixS(Img* img, int number,int size){
    matrix* m = newMatrix(size,size);
    __uint8_t* pos = img->bb->p + img->offset + (number*size*size);
        for(int i=1; i<=size; i++){
            for(int j=1; j<=size; j++){

                setElement(m,i,j,*pos);
            pos+=1;
        }
    }
    reduceto251(m);
    return m;
}


void putMatrixS(Img* img,matrix* ms,int number,int size){
    __uint8_t* pos = img->bb->p + img->offset + (number*size*size);
    for(int i=1; i<=size; i++){

        for(int j=1; j<=size; j++){


            pos[0]= (u_int8_t)ELEM(ms,i,j);
            pos+=1;
        }
    }
}



Img** read_images_from_dir(char * directory, int n) {
    int image_qty = 0;
    struct dirent *p_dirent;
    DIR* dir;
    dir = opendir(directory);
    Img** images = malloc(8 * sizeof(Img*));
    char * path;

    //assure(dir != NULL, "Problem opening directory, check your sintax.\n");
    while ((p_dirent = readdir(dir)) != NULL) {
        if(strstr(p_dirent->d_name, ".bmp") && image_qty < n && image_qty <= n) {
            path = calloc(strlen(directory) + strlen(p_dirent->d_name) + 2, 1);
            strcpy(path, directory);
            strcat(path, "/");
            strcat(path, p_dirent->d_name);

            // images[image_qty] = malloc(sizeof(image_t));
            images[image_qty++] = read_bmp(path);
            free(path);
        }
    }
    if(n!=image_qty){
        printf("No hay la cantidad de imagenes necesaria \n");
        exit(EXIT_FAILURE);
    }
    closedir(dir);

    return images;
}


int getQuantiyMatrixS(Img* img,int n){
    if(img->bits!=8){
        return -1;
    }
    return (img->height*img->width)/(n*n);
}




void putMatrixSh(Img* img,matrix* sh,int pos, int n) {
    int32_t matrix_offset =n* n * 3 * pos;

    int pasos = 2;
    if (n == 8) {
        pasos = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 3; j++) {
            int valor = ELEM(sh, i, j);
            for (int v = 0; v < n; v++) {
                set_bits(img, matrix_offset, valor, pasos);
                valor = valor << pasos;
                matrix_offset += 1;
            }

        }
    }

}
matrix* getMatrixSh(Img* img,int pos, int n){
    int32_t  matrix_offset = n*3*n*pos;
    matrix* sh=newMatrix(n,3);
    int pasos = 2;
    if (n == 8) {
        pasos = 1;
    }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=3;j++){

                uint8_t valor=0;
            for(int v=0;v<n;v++) {
                int bit = get_bits(img, matrix_offset, pasos);
                valor = valor << pasos;
                valor = valor | bit;
                matrix_offset+=1;
            }
//            valor =recover_lsb_width2(img->bb->p+(img->offset+matrix_offset),0);
            ELEM(sh,i,j)=valor;
        }



    }

    return sh;
}
