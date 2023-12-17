#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct
{
    int k;
    int numVerts;
    int numEdges;
    int **matrix;
} GraphData;

GraphData lerDados(char *filename); // le dados do ficheiro e retorna grafo
void gera_sol_inicial(int *sol, int v, int k);
void escreve_sol(int *sol, int vert);
void gera_vizinho(int a[], int b[], int n);
int calcula_fit(int a[], int **mat, int vert);
void repair_sol(int a[], int **mat, int vert);
int flip();
void init_rand();
int random_l_h(int min, int max);
float rand_01();

#endif // UTILS_H