#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arguments.h"

int main(int argc, char *argv[]){
    Configuration* cfg = parse_options(argc,argv);
    printf(cfg->m_image_name);
    printf("%d",cfg->number_k);

    exit(EXIT_SUCCESS);
    return 0 ;
}

