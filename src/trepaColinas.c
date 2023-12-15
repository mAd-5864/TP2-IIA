#include "trepaColinas.h"
#define max_iter_sem_melhora 100

void trepaColinas(GraphData grafo, int Its)
{
    int custo_atual, melhor_custo;
    int iteracoes_sem_melhora = 0;
    int *sol_atual = malloc(grafo.numVerts * sizeof(int));
    int *melhor_solucao = malloc(grafo.numVerts * sizeof(int));
    int *nova_sol = malloc(grafo.numVerts * sizeof(int));

    if (nova_sol == NULL || sol_atual == NULL || melhor_solucao == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    gera_sol_inicial(sol_atual, grafo.numVerts);
    custo_atual = calcula_fit(sol_atual, grafo.matrix, grafo.numVerts);

    // Inicializa a melhor solução com a solução inicial
    for (int i = 0; i < grafo.numVerts; ++i)
    {
        melhor_solucao[i] = sol_atual[i];
    }
    melhor_custo = custo_atual;
    for (int i = 0; i < Its; i++)
    {
        // Gera uma solução na vizinhança da solução atual
        gera_vizinho(sol_atual, nova_sol, grafo.numVerts);

        // Verifica se a nova solução viola alguma restrição e repara se necessário
        vizinhancaReparacao(sol_atual, grafo.numVerts, grafo, grafo.k);

        // Avalia a nova solução
        int novo_custo = avaliaSolucao(grafo, grafo.numVerts, sol_atual);

        // Compara com a melhor solução encontrada até agora
        if (novo_custo < melhor_custo)
        {
            // Atualiza a melhor solução
            for (int i = 0; i < grafo.numVerts; ++i)
            {
                melhor_solucao[i] = sol_atual[i];
            }
            melhor_custo = novo_custo;
            iteracoes_sem_melhora = 0; // Reseta contador de iterações sem melhora
        }
        else
        {
            iteracoes_sem_melhora++;
            if (iteracoes_sem_melhora == max_iter_sem_melhora)
            {
                return;
            }
        }
    }
}