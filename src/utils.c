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

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *sol, int v)
{
	int i, x;

	for(i=0; i<v; i++)
        sol[i]=0;
	for(i=0; i<v/2; i++)
    {
        do
			x = random_l_h(0, v-1);
        while(sol[x] != 0);
        sol[x]=1;
    }
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
	int i;

	printf("\nConjunto A: ");
	for(i=0; i<vert; i++)
		if(sol[i]==0)
			printf("%2d  ", i);
	printf("\nConjunto B: ");
	for(i=0; i<vert; i++)
		if(sol[i]==1)
			printf("%2d  ", i);
	printf("\n");
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
	srand((unsigned)time(NULL));
}