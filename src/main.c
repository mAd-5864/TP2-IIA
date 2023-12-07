// gcc main.c utils.c -o main
#include "utils.h"

int main()
{
    int opt;
    char path[100], filename[100];
    char directory[] = "../instancias/", ext[] = ".txt";
    printf("Ficheiro a ler: ");
    fgets(filename, sizeof(filename), stdin);
    strtok(filename, "\n");
    strcat(filename, ext);
    sprintf(path, "%s%s", directory, filename);

    GraphData graph = lerDados(path);

    printf("k value: %d\n", graph.k);
    printf("Number of vertices: %d\n", graph.numVerts);
    printf("Number of edges: %d\n", graph.numEdges);

    printf("Edge information:\n");
    for (int i = 0; i < graph.numEdges; i++) {
        printf("Edge %d: %d -> %d, Cost: %d\n", i + 1, graph.edges[i].vert1, graph.edges[i].vert2, graph.edges[i].custo);
    }

    free(graph.edges);

    return 0;
}
