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

void distribute(Configuration* cfg);
void recover(Configuration* cfg);



Configuration* parse_options(int argc, char *argv[]){
    Configuration* cfg=malloc(sizeof(Configuration));
    memset(cfg,0, sizeof(Configuration));
    int c;

    static struct option long_options[] = {
            {"secret",    required_argument, 0,  's' },
            {"dir",       required_argument, 0,  'i' },
            {"d",         no_argument,       0,  'd' },
            {"r",         no_argument,       0,  'r' },
            {"k",         required_argument, 0,  'k' },
            {"n",         required_argument, 0,  'n' },
            {"s",         required_argument, 0,  's' },
            {"m",         required_argument, 0,  'm' },
            {0,           0,                 0,  0   }
    };

    int long_index =0;

    while ((c = getopt_long_only(argc, argv,"", long_options, &long_index )) != -1) {
        switch (c){
            case 0:
                printf("Hew dude\n");
                break;
            case 'i':
                cfg->dir = optarg;
                break;
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

    return cfg;
}

void select_mode(Configuration* cfg){
    //TODO chekear flags invalidos


    if(cfg->number_n==0 || cfg->m_image_name==0){
        exit(EXIT_FAILURE);
    }
    if(cfg->d_mode){ //DISTRIBUTE MODE
        distribute(cfg);
    }else if(cfg->r_mode){ //RECOVER MODE
        recover(cfg);
    }

    //todo WRITE FILES!!!
    exit(EXIT_SUCCESS);

}
int c[8]={1,2,3,4,5,6,7,8};


void distribute(Configuration* cfg){
    int n= cfg->number_n;
    int k= cfg->number_k;
    Img** sh_images = read_images_from_dir(cfg->dir,n); //hay N imagenes
    Img* s_image  = read_bmp(cfg->s_image_name);
    Img* m_image  = read_bmp(cfg->s_image_name);
    for(int i=0;i<getQuantiyMatrixS(s_image,n);i++){

        matrix* ma=newMatrixA(n,k);
        matrix* mdoubles=newMatrixS(ma);

        matrix* ms=getMatrixS(s_image,i,n);
        matrix* mw=getMatrixS(m_image,i,n);

        matrix* mr=newMatrixR(ms,mdoubles);

        matrix* mrw = newMatrixRW(mw,mr);

        matrixCol* mcg = generateAllMatrixG(n,c,mr);

        matrixCol* vectorsX=getVectorsX(k,n);
        matrixCol* vectorsV=getVectorsV(ma,vectorsX);
        matrixCol* shadows = getMatrixColSh(vectorsV,mcg);

        for(int s=0;s<shadows->size;s++){
            putMatrixSh(sh_images[s],shadows->matrixes[s],i,n);
        }
        putMatrixS(m_image,mrw,i,n);
        //dont touch s_image


        //TODO FIX MEMORY LEAKS!
    }
}

void recover(Configuration* cfg){
    int n= cfg->number_n;
    int k= cfg->number_k;
    Img** shadows = read_images_from_dir(cfg->dir,n); //hay N imagenes
//    Img* m_image  = read_bmp(cfg->s_image_name);
//
//    Img* s_image = copy_img(m_image);
//    free(s_image->filename);
//    s_image->filename=cfg->s_image_name;

    for(int i=0;i<100;i++){ //todo FIX
        matrixCol* mcsh=newMatrixCol(k);
        for(int s=0;s<k;s++){
            mcsh->matrixes[s]=getMatrixSh(shadows[s],i,n);
        }
//        matrix* mb=newMatrixB(mcsh);
//        matrix* mdobleS=newMatrixS(mb);
//        matrixCol* mcg =getMatrixColG(mcsh);
//
//        matrix* mr = recoverMatrixR(mcg,c);

//        matrix* ms= recoverMatrixS(mdobleS,mr);
//
//        matrix* mrw = getMatrixS(m_image,i,n);
//
//        matrix* mw = recoverMatrixS(mdobleS,mrw);


    }
}

void help() {printf("La ayuda...\n");}

