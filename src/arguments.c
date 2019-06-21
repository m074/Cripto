#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "general.h"

int cs[8]={1,2,3,4,5,6,7,8};


void help();

void distribute(Configuration* cfg);
void recover(Configuration* cfg);

void select_mode(Configuration* cfg);


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
    select_mode(cfg);
    return cfg;
}

void select_mode(Configuration* cfg){
    //TODO chekear flags invalidos


    if(cfg->number_n==0 || cfg->m_image_name==0){
        printf("Argumentos invalidos\n");
        exit(EXIT_FAILURE);
    }
    if(cfg->d_mode){ //DISTRIBUTE MODE
        distribute(cfg);
    }else if(cfg->r_mode){ //RECOVER MODE
        recover(cfg);
    }

    exit(EXIT_SUCCESS);

}



void distribute(Configuration* cfg){


    int n= cfg->number_n;
    int k= cfg->number_k;
    Img* s_image  = read_bmp(cfg->s_image_name);
    Img* m_image  = read_bmp(cfg->m_image_name);
    Img** sh_images = read_images_from_dir(cfg->dir,n); //hay N imagenes

    for(int i=0;i<getQuantiyMatrixS(s_image,n);i++){
        matrix* ma=newMatrixA(n,k);
        matrix* mdoubles=newMatrixS(ma);
        matrix* ms=getMatrixS(s_image,i,n);
        matrix* mw=getMatrixS(m_image,i,n);
        matrix* mr=newMatrixR(ms,mdoubles);
        matrix* mrw = newMatrixRW(mw,mdoubles);
        matrixCol* mcg = generateAllMatrixG(n,cs,mr);
        matrixCol* vectorsX=getVectorsX(k,n);
        matrixCol* vectorsV=getVectorsV(ma,vectorsX);
        matrixCol* mcs = getMatrixColSh(vectorsV,mcg);

        for(int s=0;s<mcs->size;s++){
            putMatrixSh(sh_images[s],mcs->matrixes[s],i,n);

        }

        if(i==0){
            printf("Matrix la Sdoble\n");
            printMatrix(mdoubles);
            printf("Matrix la S\n");
            printMatrix(ms);
            printf("Matrix la RW\n");
            printMatrix(mrw);
            for(int kk=0;kk<mcs->size;kk++){
                printf("Shadow\n");
                printMatrix(mcs->matrixes[kk]);
            }
        }


        putMatrixS(m_image,mrw,i,n);
        //dont touch s_image

        deleteMatrix(ma);
        deleteMatrix(mdoubles);
        deleteMatrix(ms);
        deleteMatrix(mw);
        deleteMatrix(mr);
        deleteMatrix(mrw);
        deleteMatrixCol(mcg);
        deleteMatrixCol(vectorsX);
        deleteMatrixCol(vectorsV);
        deleteMatrixCol(mcs);


    }
    writefile(m_image->bb,"alaa.bmp"); //TODO RW IMAGE

    for(int ar=0;ar<n;ar++){
        writefile(sh_images[ar]->bb,sh_images[ar]->filename);
    }


    deleteImg(s_image);
    deleteImg(m_image);
    for(int sh=0;sh<n;sh++){
        deleteImg(sh_images[sh]);
    }
    free(sh_images);
}

void recover(Configuration* cfg){
    int n= cfg->number_n;
    int k= cfg->number_k;

    Img* rw_image  = read_bmp(cfg->m_image_name);
    Img** sh_images = read_images_from_dir(cfg->dir,k); //hay N imagenes

    Img* s_image = copy_img(rw_image);
    change_filename(s_image,cfg->s_image_name);

    Img* w_image = copy_img(rw_image);
    change_filename(w_image,"watermark.bmp");

    for(int i=0;i<getQuantiyMatrixS(rw_image,n);i++){
        matrixCol* mcsh=newMatrixCol(k);
        for(int s=0;s<k;s++){
            mcsh->matrixes[s]=getMatrixSh(sh_images[s],i,n);
        }

        matrix* mb=newMatrixB(mcsh,k);
        matrix* mdobleS=newMatrixS(mb);

        matrixCol* mcg =getMatrixColG(mcsh,k);


        matrix* mr = recoverMatrixR(mcg,cs);

        matrix* ms= recoverMatrixS(mdobleS,mr);

        matrix* mrw = getMatrixS(rw_image,i,n);

        matrix* mw = recoverMatrixS(mdobleS,mrw);

        putMatrixS(s_image,ms,i,n);
        putMatrixS(w_image,mw,i,n);

        if(i==0){

            printf("Matrix la B\n");
            printMatrix(mb);
            printf("Matrix la R\n");
            printMatrix(mr);
            printf("Matrix la Sdoble\n");
            printMatrix(mdobleS);
            printf("Matrix la S\n");
            printMatrix(ms);
            printf("Matrix la RW\n");
            printMatrix(mrw);
            for(int kk=0;kk<mcsh->size;kk++){
                printf("Shadow\n");
                printMatrix(mcsh->matrixes[kk]);
            }

            for(int kk=0;kk<mcsh->size;kk++){
                printf("gg\n");
                printMatrix(mcg->matrixes[kk]);
            }
        }

        deleteMatrix(ms);
        deleteMatrix(mb);
        deleteMatrix(mw);
        deleteMatrix(mr);
        deleteMatrix(mrw);
        deleteMatrix(mdobleS);
        deleteMatrixCol(mcg);
        deleteMatrixCol(mcsh);
    }
    writefile(s_image->bb,"sss.bmp");
    writefile(w_image->bb,w_image->filename);

    deleteImg(s_image);
    deleteImg(rw_image);
    deleteImg(w_image);
    for(int sh=0;sh<k;sh++){
        deleteImg(sh_images[sh]);
    }
    free(sh_images);
}

void help() {printf("La ayuda...\n");}

