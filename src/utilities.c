//
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

    i %= 251;
    if (i < 1 || i > 251) {
        return -1;
    }
    return inverses[i - 1];
}

int multiplicativeInverse(int a)
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
