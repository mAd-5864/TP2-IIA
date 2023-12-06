#include "utils.h"

int main()
{
    char filename[100];
    int opt;

     printf("Ficheiro a ler: ");
    fgets(filename,100,stdin);
    strtok(filename,"\n");

   GraphData graph = lerDados(filename);

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
