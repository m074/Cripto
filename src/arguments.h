#ifndef CRIPTO_ARGUMENTS_H
#define CRIPTO_ARGUMENTS_H
typedef struct conf_t
{
    int d_mode;
    int r_mode;
    char* s_image_name;
    char* m_image_name;
    int number_k;
    int number_n;
} Configuration;

Configuration* parse_options(int argc, char *argv[]);

#endif //CRIPTO_ARGUMENTS_H
