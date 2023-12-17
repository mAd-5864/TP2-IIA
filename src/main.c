// gcc main.c utils.c trepaColinas.c algoritmoEvolutivo.c -o main
#include "trepaColinas.h"
#include "algoritmoEvolutivo.h"

int main()
{
    int opt, num_iter, num_runs, custo, custo_total = 0, melhor_custo = INT_MAX;
    float mbf = 0;
    char path[100], filename[100];
    char directory[] = "../instancias/", ext[] = ".txt";
    printf("Ficheiro a ler: ");
    fgets(filename, sizeof(filename), stdin);
    strtok(filename, "\n");
    strcat(filename, ext);
    sprintf(path, "%s%s", directory, filename);

    // GraphData graph = lerDados("../instancias/test.txt");
    GraphData graph = lerDados(path);

    // Infos ficheiro lido
    printf("Valor K: %d\n", graph.k);
    printf("Num Vertices: %d\n", graph.numVerts);
    printf("Ligacoes: %d\n", graph.numEdges);

    // inicia numeros aleatorios
    init_rand();

    // solucao inicial
    int *sol_inic = malloc(sizeof(int) * graph.k);

    int *sol_best = malloc(sizeof(int) * graph.k);

    if (sol_inic == NULL || sol_best == NULL)
    {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    // Menu
    printf("1 - Trepa Colinas\n");
    printf("2 - Algoritmo Evolutivo\n");
    printf("3 - Algoritmo Hibrido\n");
    printf("Escolha: ");
    scanf("%d", &opt);

    if (opt == 1)
    {
        printf("Quantas runs deseja fazer: ");
        scanf("%d", &num_runs);

        printf("Quantas iteracoes deseja fazer: ");
        scanf("%d", &num_iter);

        for (int i = 0; i < num_runs; i++)
        {
            custo = trepaColinas(graph, num_iter);
            custo_total += custo;
            if (custo < melhor_custo)
                melhor_custo = custo;
        }
        mbf = custo_total / (float)num_runs;
        printf("\nMBF: %.3f\n", mbf);
    }
    else if (opt == 2)
    {
        printf("Quantas runs deseja fazer: ");
        scanf("%d", &num_runs);

        struct info d;

        d.popsize = 500;
        d.pm = 0.01;
        d.pr = 0.8;
        d.tsize = 2;
        d.ro = 0.9;
        d.numGenes = graph.numVerts;
        d.capacity = graph.k;
        d.numGenerations = graph.numEdges / 2;
        for (int i = 0; i < num_runs; i++)
        {
            custo = algoritmoEvolutivo(graph, d);
            custo_total += custo;
            if (custo < melhor_custo)
                melhor_custo = custo;
        }
    }
    printf("\nMelhor Custo: %d\n", melhor_custo);
    mbf = custo_total / (float)num_runs;
    printf("\nMBF: %.3f\n", mbf);

    free(graph.matrix);
    return 0;
}
