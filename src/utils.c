#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

GraphData lerDados(char *filename)
{
    FILE *file;
    GraphData graph;

    file = fopen(filename, "r");
    if (!file)
    {
        printf("Erro ao abrir o ficheiro\n");
        exit(1);
    }

    // Read k value from the first line
    fscanf(file, "%*s %d", &graph.k);

    // Read number of vertices (numVerts) and number of edges (numEdges)
    fscanf(file, "%*s %*s %d %d", &graph.numVerts, &graph.numEdges);

    // Allocate memory for the matrix
    graph.matrix = (int **)malloc(graph.numVerts * sizeof(int *));
    for (int i = 0; i < graph.numVerts; i++)
    {
        graph.matrix[i] = (int *)calloc(graph.numVerts, sizeof(int));
    }

    int v1, v2, cost;
    char type;
    for (int i = 0; i < graph.numEdges; i++)
    {
        fscanf(file, " %c %d %d %d", &type, &v1, &v2, &cost);
        graph.matrix[v1 - 1][v2 - 1] = cost;
        graph.matrix[v2 - 1][v1 - 1] = cost;
    }

    fclose(file);
    return graph;
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *sol, int v)
{
    int i, x;

    for (i = 0; i < v; i++)
        sol[i] = 0;
    for (i = 0; i < v / 2; i++)
    {
        do
            x = random_l_h(0, v - 1);
        while (sol[x] != 0);
        sol[x] = 1;
    }
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
    int i;

    printf("\nConjunto A: ");
    for (i = 0; i < vert; i++)
        if (sol[i] == 0)
            printf("%2d  ", i);
    printf("\nConjunto B: ");
    for (i = 0; i < vert; i++)
        if (sol[i] == 1)
            printf("%2d  ", i);
    printf("\n");
}

void gera_vizinho(int a[], int b[], int n)
{
    int i, p1, p2;

    // Copia a solu��o atual para a solu��o vizinha
    for (i = 0; i < n; i++)
        b[i] = a[i];
    // Encontra aleatoriamente a posi��o de um v�rtice com valor 0
    do
        p1 = random_l_h(0, n - 1);
    while (b[p1] != 0);
    // Encontra aleatoriamente a posi��o de um v�rtice com valor 1
    do
        p2 = random_l_h(0, n - 1);
    while (b[p2] != 1);
    // Troca os valores dos v�rtices das posi��es encontradas
    b[p1] = 1;
    b[p2] = 0;
}

// Calcula a qualidade de uma solu��o
// Recebe:  A solu��o, a, a matriz de adjac�ncias, mat, e o n�mero de v�rtices, vert
// Devolve: O custo que � o n�mero de liga��es que existem na solução
int calcula_fit(int a[], int *mat, int vert)
{
    int total = 0;
    int i, j;

    for (i = 0; i < vert; i++)
        if (a[i] == 0)
        {
            for (j = 0; j < vert; j++)
                if (a[j] == 1 && *(mat + i * vert + j) == 1)
                    total++;
        }
    return total;
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        a[i] = b[i];
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
    srand((unsigned)time(NULL));
}
// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01()
{
    return ((float)rand()) / RAND_MAX;
}