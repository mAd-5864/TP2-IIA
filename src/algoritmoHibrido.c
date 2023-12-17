#include "algoritmoEvolutivo.h"
#include "trepaColinas.h"

int algoritmoHibrido(GraphData grafo, struct info d, int Its)
{
    int i;
    pchrom population = init_pop(d);
    for (int i = 0; i < d.popsize; i++)
    {
        repair_sol(population[i].p, grafo.matrix, d.numGenes);
    }

    // Evaluate populacao inicial
    evaluate(population, d, grafo.matrix);

    chrom best_solution;
    best_solution.fitness = INT_MAX;

    // Trepa-colinas para cada solucao
    for (i = 0; i < d.popsize; ++i)
    {
        int *nova_sol = malloc(grafo.numVerts * sizeof(int));
        for (int h = 0; h < Its; h++)
        {
            //  Gera uma solução na vizinhança da solução atual
            gera_vizinho(population[i].p, nova_sol, grafo.numVerts);
            // Verifica se a nova solução viola alguma restrição e repara se necessário
            repair_sol(nova_sol, grafo.matrix, grafo.numVerts);

            // Avalia a nova solução
            int novo_custo = calcula_fit(nova_sol, grafo.matrix, grafo.numVerts);

            // Compara com a melhor solução encontrada até agora
            if (novo_custo < best_solution.fitness)
            {

                // Atualiza a melhor solução
                for (int j = 0; j < grafo.numVerts; ++j)
                {
                    best_solution.p[j] = population[i].p[j];
                }
                best_solution.fitness = novo_custo;
            }
            else if (novo_custo < population[i].fitness)
            {
                for (int j = 0; j < grafo.numVerts; ++j)
                {
                    best_solution.p[j] = population[i].p[j];
                }
                population[i].fitness = novo_custo;
            }
        }
    }

    // Parte evolutiva
    for (i = 0; i < d.numGenerations; ++i)
    {
        // Select parents
        pchrom parents = (pchrom)malloc(sizeof(chrom) * d.popsize);
        tournament(population, d, parents);

        // Aplicar crossover and mutation
        pchrom offspring = (pchrom)malloc(sizeof(chrom) * d.popsize);
        genetic_operators(parents, d, offspring);

        // Evaluate offspring
        evaluate(offspring, d, grafo.matrix);

        // Select individuals for the next generation
        free(population);
        population = offspring;

        best_solution = get_best(population, d, best_solution);

        // Clean up memory
        free(parents);
    }

    // Find the best solution
    best_solution = get_best(population, d, best_solution);

    escreve_sol(best_solution.p, d.numGenes);
    printf("Custo: %.0f\n", best_solution.fitness);

    // Clean up memory
    free(population);

    // Return the best solution's fitness or cost
    return best_solution.fitness;
}