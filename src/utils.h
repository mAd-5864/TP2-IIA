#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int vert1;
    int vert2;
    int custo;
} Edge;

typedef struct {
    int k;
    int numVerts;
    int numEdges;
    Edge *edges;
} GraphData;

GraphData lerDados(char *filename); // le dados do ficheiro e retorna grafo