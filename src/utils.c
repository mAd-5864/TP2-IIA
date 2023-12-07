#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

GraphData lerDados(char *filename) {
    FILE *file;
    GraphData graph;

    file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o ficheiro\n");
        exit(1);
    }

    // Read k value from the first line
    fscanf(file, "%*s %d", &graph.k);

    // Read number of vertices (numVerts) and number of edges (numEdges)
    fscanf(file, "%*s %*s %d %d", &graph.numVerts, &graph.numEdges);

    graph.edges = (Edge *)malloc(graph.numEdges * sizeof(Edge));

    if (!graph.edges) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    for (int i = 0; i < graph.numEdges; i++) {
        char type;
        fscanf(file, " %c %d %d %d", &type, &graph.edges[i].vert1, &graph.edges[i].vert2, &graph.edges[i].custo);
    }

    fclose(file);

    return graph;
}