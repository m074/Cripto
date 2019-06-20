#include "random.h"

void
setSeed(int64_t s)
{
    seed = (s ^ 0x5DEECE66DL) & ((1LL << 48) - 1);
}

uint8_t
nextChar(void){
    seed = (seed * 0x5DEECE66DL + 0xBL) & ((1LL << 48) - 1);
    return (uint8_t)(seed>>40);
}

uint8_t
nextCharLimit(uint8_t limit){
    seed = (seed * 0x5DEECE66DL + 0xBL) & ((1LL << 48) - 1);
    return (uint8_t)(seed>>40) % limit;
}


