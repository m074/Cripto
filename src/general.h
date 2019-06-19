#ifndef CRIPTO_GENERAL_H
#define CRIPTO_GENERAL_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include "matrix.h"


#define WIDTH_HEADER_OFFSET 0x12
#define WIDTH_HEADER_SIZE 0x4

#define HEIGHT_HEADER_OFFSET 0x16
#define HEIGHT_HEADER_SIZE 0x4

// Amount bits per pixel
#define BITS_PER_PIXEL_HEADER_OFFSET 0x1C
#define BITS_PER_PIXEL_HEADER_SIZE 0x2

// Compression
#define COMPRESSION_HEADER_OFFSET 0x1E
#define COMPRESSION_HEADER_SIZE 0x4

#define BODY_START_HEADER_OFFSET 0x0A
#define BODY_START_HEADER_SIZE 0x4


typedef struct byte_buffer_t
{
    u_int8_t *p;
    u_int32_t length;
} BBuffer;

typedef struct bmp_t
{
    char*      filename;
    u_int32_t  width;
    u_int32_t  height;
    u_int8_t   bits;
    u_int32_t  offset;
    BBuffer*   bb;
} Img;

typedef struct conf_t
{
    int d_mode;
    int r_mode;
    char* s_image_name;
    char* m_image_name;
    char* dir;
    int number_k;
    int number_n;
} Configuration;

Configuration* parse_options(int argc, char *argv[]);

BBuffer* readfile(char* filename);

int writefile(BBuffer* bb, char* filename);

BBuffer* copy_bbuffer(BBuffer* bb);

void free_bbuffer(BBuffer* bb);

Img* read_bmp(char* filename);

void change_filename(Img* img,char* filename);

Img** read_images_from_dir(char * directory, int n);

matrix* getMatrixS(Img* img, int number,int size);

void putMatrixS(Img* img,matrix* ms,int number,int size);

Img* copy_img(Img* img);

int getQuantiyMatrixS(Img* img,int n);

matrix* getMatrixSh(Img* img,int pos, int n);

void putMatrixSh(Img* img,matrix* sh,int pos, int n);

u_int8_t get_bits(Img* img,u_int32_t pos, int bits);

void deleteImg(Img* img);

void set_bits(Img* img,u_int32_t pos, u_int8_t value, int bits);

#endif //CRIPTO_GENERAL_H
