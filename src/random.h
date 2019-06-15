

#ifndef CRIPTO_RANDOM_H
#define CRIPTO_RANDOM_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>


#define MAX 50
#define SET 10
/*variable global*/
int64_t seed; /*seed debe ser de 48 bits; se elige este tipo de 64 bits*/
void setSeed(int64_t seed);
uint8_t nextChar(void); /*devuelve un unsigned char*/
#endif //CRIPTO_RANDOM_H
