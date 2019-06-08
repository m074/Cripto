#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"


//-d o bien –r
// -s imagenSecreta
// -m imagenMarca
// -k número
// -n número
// -dir directorio
//Significado de cada uno de los parámetros obligatorios:
// -d: indica que se va a distribuir una imagen secreta en otras imágenes.
// –r: indica que se va a recuperar una imagen secreta a partir de otras imágenes.
// -s imagen: El nombre imagen corresponde al nombre de un archivo de extensión .bmp. En el
//caso de que se haya elegido la opción (-d) este archivo debe existir ya que es la imagen a
//ocultar y debe ser una imagen en blanco y negro (8 bits por pixel) Si se eligió la opción (-r)
//éste archivo será el archivo de salida, con la imagen secreta revelada al finalizar el programa.
// -m imagen: El nombre imagen corresponde al nombre de un archivo con extensión .bmp. En el
//caso de que se haya elegido la opción (-d) este archivo es una imagen en blanco y negro que
//servirá como “marca de agua” para verificar tdo el proceso. Debe ser de igual tamaño que la
//        imagen secreta. En el caso de que se haya elegido la opción (-r) este archivo es una imagen en
//blanco y negro que contiene la transformación de la imagen de “marca de agua”.
// -k número: El número corresponde a la cantidad mínima de sombras necesarias para
//        recuperar el secreto en un esquema (k, n).
// -n número: El número corresponde a la cantidad total de sombras en las que se distribuirá
//el secreto en un esquema (k, n).
// -dir directorio El directorio donde se encuentran las imágenes en las que se distribuirá el
//secreto (en el caso de que se haya elegido la opción (-d)), o donde están las imágenes que
//contienen oculto el secreto ( en el caso de que se haya elegido




void help();


Configuration* parse_options(int argc, char *argv[]){
    Configuration* cfg=malloc(sizeof(Configuration));
    int c;
    while ((c = getopt (argc, argv, "hi:d:r:s:m:k:n")) != -1){
        switch (c){
//            case 0:
//                printf("ASDADSASDAS");
//                break;
            case 'd':
                cfg->d_mode = 1;
                break;
            case 'r':
                cfg->r_mode = 1;
                break;
            case 's':
                cfg->s_image_name = optarg;
                break;
            case 'm':
                cfg->m_image_name = optarg;
                break;
            case 'k':
                cfg->number_k = atoi(optarg);
                break;
            case 'n':
                cfg->number_n = atoi(optarg);
                break;
            case 'h':
                help();
                exit(EXIT_SUCCESS);

            default:
                abort();
        }
    }
    //TODO checks

    return cfg;
}

void help() {
    printf("La ayuda...\n");
}
