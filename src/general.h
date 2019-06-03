#ifndef CRIPTO_GENERAL_H
#define CRIPTO_GENERAL_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>



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
    u_int32_t  width;
    u_int32_t  height;
    u_int8_t   bits;
    u_int32_t  offset;
    BBuffer*   bb;
} Bmp;

typedef struct conf_t
{
    int d_mode;
    int r_mode;
    char* s_image_name;
    char* m_image_name;
    int number_k;
    int number_n;
} Configuration;


Bmp* read_bmp(char* filename);

BBuffer* readfile(char* filename);

Configuration* parse_options(int argc, char *argv[]);

#endif //CRIPTO_GENERAL_H
