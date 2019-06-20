
#include "general.h"

BBuffer* readfile(char* filename){
    FILE *fd;
    printf("Abriendo el archivo: %s\n",filename);
    if ((fd = fopen(filename, "rb")) == NULL)
    {
        return NULL;
    }
    BBuffer* bb = malloc(sizeof(BBuffer));

    fseek(fd, 0, SEEK_END);
    u_int32_t size = ftell(fd);
    bb->length = size;
    bb->p = malloc(size);
    fseek(fd, 0, SEEK_SET);

    if (fread(bb->p, 1, bb->length, fd) != (size_t)bb->length){

        return NULL;
    }

    fclose(fd);


    return bb;
}

int writefile(BBuffer* bb, char* filename){
    FILE *fd;
    if ((fd = fopen(filename, "wb")) == NULL)
    {
        return 0;
    }
    fwrite(bb->p,1,bb->length,fd); //TODO arreglar
    fclose(fd);
    return 1;
}


BBuffer* copy_bbuffer(BBuffer* bb){
    BBuffer* bb2 = malloc(sizeof(BBuffer));
    bb2->length = bb->length;
    bb2->p = malloc((bb->length));
    memcpy(bb2->p,bb->p,bb->length);

    return bb2;
}

void free_bbuffer(BBuffer* bb){
        free(bb->p);
        free(bb);
}
