#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "general.h"
#include "matrix.h"
#include "utilities.h"
#include "random.h"


int main(int argc, char *argv[]){
    setSeed(time(0));

    parse_options(argc,argv);

}

