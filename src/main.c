// gcc main.c utils.c -o main
#include "utils.h"

int main()
{
    int opt, num_iter;
    char path[100], filename[100];
    char directory[] = "../instancias/", ext[] = ".txt";
    printf("Ficheiro a ler: ");
    fgets(filename, sizeof(filename), stdin);
    strtok(filename, "\n");
    strcat(filename, ext);
    sprintf(path, "%s%s", directory, filename);

    GraphData graph = lerDados(path);

    // Infos ficheiro lido
    printf("k value: %d\n", graph.k);
    printf("Number of vertices: %d\n", graph.numVerts);
    printf("Number of edges: %d\n", graph.numEdges);
    printf("Edge information:\n");
    for (int i = 0; i < graph.numEdges; i++)
    {
        printf("Edge %d: %d -> %d, Cost: %d\n", i + 1, graph.edges[i].vert1, graph.edges[i].vert2, graph.edges[i].custo);
    }

    // inicia numeros aleatorios
    init_rand();

    // Menu
    printf("1 - Trepa Colinas\n");
    printf("2 - Algoritmo Evolutivo\n");
    printf("3 - Algoritmo Hibrido\n");
    printf("Escolha: ");
    scanf("%d", &opt);

    if (opt == 1)
    {
        printf("Quantas iteracoes deseja fazer: ");
        scanf("%d", &num_iter);
        /*TREPA COLINAS*/

        // solucao inicial
        int *sol_inic = malloc(sizeof(int) * graph.k);

        int *sol_best = malloc(sizeof(int) * graph.k);

        if (sol_inic == NULL || sol_best == NULL)
        {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }

        free(graph.edges);

        return 0;
    }
