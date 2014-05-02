#include <stdio.h>
#include <stdlib.h>

typedef int TELEMENTO;

typedef struct {
    int tam;
    TELEMENTO *datos;
} STMATRIZ;
typedef STMATRIZ *TMATRIZ;

void crear(TMATRIZ *matrix,int size){
    int i=0;
 
    *matrix=(TMATRIZ)malloc(sizeof(STMATRIZ));
    (*matrix)->tam = size;
    size=size*size;
    (*matrix)->datos=(TELEMENTO*)malloc(size*sizeof(TELEMENTO));
    for (i = 0; i <size ; i++)
        *((*matrix)->datos + i) = 0;
    
}

void destruir(TMATRIZ *matrix) {
    if (matrix != NULL) {
        free((*matrix)->datos);
        free(*matrix);
    }
}

void asignar(TMATRIZ *matrix, int x,int y, TELEMENTO valor) {
    if(matrix != NULL && (*matrix)->datos != NULL && x>=0 && y>=0 && x<(*matrix)->tam && y<(*matrix)->tam)
        *((*matrix)->datos + x*(*matrix)->tam + y) = valor;
}

void recuperar(TMATRIZ matrix, int x, int y, TELEMENTO *d) {
    if(matrix != NULL && matrix->datos != NULL && x>=0 && y>=0 && x<matrix->tam && y<=matrix->tam)
        *d = *(matrix->datos + x*matrix->tam +y);
}

void tamano(TMATRIZ matrix, int *t) {
    if(matrix != NULL)
        *t = matrix->tam;
    else
        *t=-1;
}