/* 
 * File:   main.c
 * Author: entakitos
 *
 * Created on 31 de marzo de 2014, 17:59
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrices.h"
/*
 * 
 */
void imprimeMatriz(TMATRIZ matrix);
void rellenaMatriz(TMATRIZ *matrix);
void sumaMatrices(TMATRIZ ma, TMATRIZ mb, TMATRIZ *mr);
void multiplicaMatrices(TMATRIZ ma, TMATRIZ mb, TMATRIZ *mr);
void acoplaMatrices(TMATRIZ m1, TMATRIZ m2, TMATRIZ m3, TMATRIZ m4, TMATRIZ *mr);
void separarMatrices(TMATRIZ src, TMATRIZ *A, TMATRIZ *B, TMATRIZ *C, TMATRIZ *D);
void multiplica(TMATRIZ A, TMATRIZ B, TMATRIZ *res);

int main(int argc, char** argv) {

    TMATRIZ m, m2,m3,m4, mr;
    int size = 0;
    do {
        printf("De que tamaño desea crear a matriz? ");
        scanf(" %d", &size);
    } while (size <= 0);

    srand(time(NULL));

    crear(&m, size);
    rellenaMatriz(&m);
    printf("\nMATRIZ A");
    printf("\n========\n");
    imprimeMatriz(m);
    printf("\n");

    crear(&m2, size);
    rellenaMatriz(&m2);
    printf("\nMATRIZ B");
    printf("\n========\n");
    imprimeMatriz(m2);
    printf("\n");

    sumaMatrices(m, m2, &mr);
    printf("\nMATRIZ SUMA");
    printf("\n============\n");
    imprimeMatriz(mr);
    printf("\n");

    destruir(&mr);
    multiplicaMatrices(m, m2, &mr);
    printf("\nMATRIZ MULTIPLICACION");
    printf("\n=====================\n");
    imprimeMatriz(mr);
    printf("\n");

    destruir(&mr);
    acoplaMatrices(m, m2, m, m2, &mr);
    printf("\nACOPLA MATRICES");
    printf("\n=====================\n");
    imprimeMatriz(mr);
    printf("\n");

    separarMatrices(mr,&m,&m2,&m3,&m4);
    
    printf("\nSEPARA MATRICES");
    printf("\n=====================\n");
    imprimeMatriz(m);
    printf("\n");
    imprimeMatriz(m2);
    printf("\n");
    imprimeMatriz(m3);
    printf("\n");
    imprimeMatriz(m4);
    printf("\n");
    
    destruir(&mr);
    
    multiplicaMatrices(m, m2, &mr);
    printf("\nMATRIZ MULTIPLICACION");
    printf("\n=====================\n");
    imprimeMatriz(mr);
    destruir(&mr);
    printf("\n");
    multiplica(m,m2,&mr);
    imprimeMatriz(mr);
    printf("\n");
    
    destruir(&m);
    destruir(&m2);
    destruir(&m3);
    destruir(&m4);
    destruir(&mr);
    return (EXIT_SUCCESS);
}

void rellenaMatriz(TMATRIZ *matrix) {
    int randm, size, x, y;
    tamano(*matrix, &size);

    for (x = 0; x < size; x++)
        for (y = 0; y < size; y++) {
            randm = rand() % 9;
            asignar(matrix, x, y, randm);
        }
}

void imprimeMatriz(TMATRIZ matrix) {
    TELEMENTO data;
    int size, x, y;
    tamano(matrix, &size);

    for (x = 0; x < size; x++) {
        for (y = 0; y < size; y++) {
            recuperar(matrix, x, y, &data);
            printf("\t %d", data);
        }
        printf("\n");
    }

}

void sumaMatrices(TMATRIZ ma, TMATRIZ mb, TMATRIZ *mr) {
    int tam1, tam2, x, y, v1, v2;

    tamano(ma, &tam1);
    tamano(mb, &tam2);

    if (tam1 == tam2) {
        crear(mr, tam1);
        for (x = 0; x < tam1; x++)
            for (y = 0; y < tam1; y++) {
                recuperar(ma, x, y, &v1);
                recuperar(mb, x, y, &v2);
                asignar(mr, x, y, v1 + v2);
            }

    } else {
        printf("Tamaño de matrices incompatible");
    }

}

void multiplicaMatrices(TMATRIZ ma, TMATRIZ mb, TMATRIZ *mr) {
    int tam1, tam2, x, y, z, res, v1, v2;

    tamano(ma, &tam1);
    tamano(mb, &tam2);

    if (tam1 == tam2) {
        crear(mr, tam1);
        for (x = 0; x < tam1; x++)
            for (y = 0; y < tam1; y++) {
                res = 0;
                for (z = 0; z < tam1; z++) {
                    recuperar(ma, x, z, &v1);
                    recuperar(mb, z, y, &v2);
                    res += v1*v2;
                }
                asignar(mr, x, y, res);
            }

    } else {
        printf("Tamaño de matrices incompatible");
    }
}

void acoplaMatrices(TMATRIZ m1, TMATRIZ m2, TMATRIZ m3, TMATRIZ m4, TMATRIZ *mr) {
    int tam, i, j, offset, aux;

    tamano(m1, &tam);
    offset = tam;
    tam = tam * 2;

    crear(mr, tam);

    for (i = 0; i < tam; i++)
        for (j = 0; j < tam; j++)
            if (i < offset && j < offset) {
                recuperar(m1, i, j, &aux);
                asignar(mr, i, j, aux);
            } else if (i < offset && j >= offset) {
                recuperar(m2, i, j - offset, &aux);
                asignar(mr, i, j, aux);
            } else if (i >= offset && j < offset) {
                recuperar(m3, i - offset, j, &aux);
                asignar(mr, i, j, aux);
            } else {
                recuperar(m4, i - offset, j - offset, &aux);
                asignar(mr, i, j, aux);
            }

}

void separarMatrices(TMATRIZ src, TMATRIZ *A, TMATRIZ *B, TMATRIZ *C, TMATRIZ *D) {
    int n, m, i, j;
    TELEMENTO elem;
    
    tamano(src, &n);
    m = n / 2;

    crear(A, m);
    crear(B, m);
    crear(C, m);
    crear(D, m);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++){
            recuperar(src,i,j,&elem);
            if (i < m && j < m) {
                asignar(A, i, j,elem);
            } else if (i >= m && j < m) {
                asignar(B, i-m, j,elem);   
            } else if (i < m && j >= m) {
                asignar(C, i, j-m,elem);
            } else {
                asignar(D, i-m, j-m,elem);
            }
        }
    }
}

void multiplica(TMATRIZ A, TMATRIZ B, TMATRIZ *res) {
    TMATRIZ A1,A2,A3,A4,B1,B2,B3,B4,C1,C2,C3,C4,aux1,aux2;
    int tam;
    
    tamano(A, &tam);
    
    if (tam <= 2) {
        multiplicaMatrices(A, B, res);
    } else {
        separarMatrices(A,&A1,&A2,&A3,&A4);
        separarMatrices(B,&B1,&B2,&B3,&B4);
        
        multiplica(A1,B1,&aux1);
        multiplica(A2,B3,&aux2);
        sumaMatrices(aux1,aux2,&C1);
        destruir(&aux1);
        destruir(&aux2);
        
        multiplica(A1,B2,&aux1);
        multiplica(A2,B4,&aux2);
        sumaMatrices(aux1,aux2,&C2);
        destruir(&aux1);
        destruir(&aux2);
        
        destruir(&A1);
        destruir(&A2);
        
        multiplica(A3,B1,&aux1);
        multiplica(A4,B3,&aux2);
        sumaMatrices(aux1,aux2,&C3);
        destruir(&aux1);
        destruir(&aux2);
        
        destruir(&B1);
        destruir(&B3);
        
        multiplica(A3,B2,&aux1);
        multiplica(A4,B4,&aux2);
        sumaMatrices(aux1,aux2,&C4);
        destruir(&aux1);
        destruir(&aux2);
            
        destruir(&A3);
        destruir(&A4);
        destruir(&B2);
        destruir(&B4);
        
        acoplaMatrices(C1,C2,C3,C4,res);
        
        destruir(&C1);
        destruir(&C2);
        destruir(&C3);
        destruir(&C4);
    }
}