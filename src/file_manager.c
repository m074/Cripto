#include "general.h"

BBuffer* readfile(char* filename){
    FILE *fd;
    if ((fd = fopen(filename, "rb")) == NULL)
    {
        return NULL;
    }
    BBuffer* bb = malloc(sizeof(BBuffer));

    fseek(fd, 0, SEEK_END);
    u_int32_t size = ftell(fd);
    bb->length = size;
    bb->p = malloc(sizeof(size));
    fseek(fd, 0, SEEK_SET);

    if (fread(bb->p, 1, bb->length, fd) != bb->length){
        return NULL;
    }

//    fclose(fd);
//TODO ver porque crashea el fclose


    return bb;
}
