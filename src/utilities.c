// Created by Esteban Kramer on 14/06/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

void assure(int truth, char* message) {
    if (!truth) {
        printf("%s", message);
        exit(0);
    }
}

int modInverse(int i) {
    while(i<=0){
        i+=251;
    }
    i %= 251;
    if (i < 1 || i > 251) {
        return -1;
    }
    return inverses[i - 1];
}

int32_t multiplicativeInverse(int a)
{
    int b = 251;
    int t, nt, r, nr, q, tmp;
    if (b < 0) b = -b;
    if (a < 0) a = b - (-a % b);
    t = 0;  nt = 1;  r = b;  nr = a % b;
    while (nr != 0) {
        q = r/nr;
        tmp = nt;  nt = t - q*nt;  t = tmp;
        tmp = nr;  nr = r - q*nr;  r = tmp;
    }
    if (r > 1) return -1;  /* No inverse */
    if (t < 0) t += b;
    return t;
}

uint32_t modProd(uint32_t a, uint32_t b)
{

    long double x;
    uint32_t c;
    int32_t r;
    if (a >= 251)
        a %= 251;
    if (b >= 251)
        b %= 251;
    x = a;
    c = x * b / 251;
    r = (int32_t)(a * b - c * 251) % (int32_t)251;
    return r < 0 ? r + 251 : r;
}

int32_t modNorm(uint8_t i){
    while(i<=0){
        i+=251;
    }
    i %= 251;
    return i;
}

