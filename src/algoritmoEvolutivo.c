#include "algoritmoEvolutivo.h"

int algoritmoEvolutivo(GraphData grafo, struct info d)
{
    pchrom population = init_pop(d);
    for (int i = 0; i < d.popsize; i++)
    {
        repair_sol(population[i].p, grafo.matrix, d.numGenes);
    }

    // Evaluate initial population
    evaluate(population, d, grafo.matrix);

    chrom best_solution;
    best_solution.fitness = INT_MAX;

    for (int gen = 0; gen < d.numGenerations; gen++)
    {
        // Select parents
        pchrom parents = (pchrom)malloc(sizeof(chrom) * d.popsize);
        tournament(population, d, parents);
        // repair_sol(parents->p, grafo.matrix, d.numGenes);

        for (int i = 0; i < d.popsize; i++)
        {
            escreve_sol(population[i].p, d.numGenes);
            printf("Teste gen %d Custo: %.0f\n", gen, population[i].fitness);
        }
        // // Apply crossover and mutation
        // pchrom offspring = (pchrom)malloc(sizeof(chrom) * d.popsize);
        // genetic_operators(parents, d, offspring);

        // // Evaluate offspring
        // // evaluate(parents, d, grafo.matrix);
        // evaluate(offspring, d, grafo.matrix);

        // // Select individuals for the next generation
        // // For simplicity, just replace old population with new offspring
        // free(population);
        // population = offspring;

        // Find and save the best solution so far
        best_solution = get_best(population, d, best_solution);

        // Clean up memory
        free(parents);
        // free(offspring);
    }

    // Print the best solution
    escreve_sol(best_solution.p, d.numGenes);
    printf("Custo: %.0f\n", best_solution.fitness);
    // write_best(best_solution, d);

    // Clean up memory
    free(population);

    // Return the best solution's fitness or cost
    return best_solution.fitness;
}

pchrom init_pop(struct info d)
{
    pchrom indiv;
    int x;
    indiv = malloc(sizeof(chrom) * d.popsize);
    if (indiv == NULL)
    {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
    for (int i = 0; i < d.popsize; i++)
        for (int j = 0; j < d.capacity; j++)
            indiv[i].p[j] = 0;

    for (int i = 0; i < d.popsize; i++)
    {
        gera_sol_inicial(indiv[i].p, d.numGenes, d.capacity);
    }
    return indiv;
}

chrom get_best(pchrom pop, struct info d, chrom best)
{

    for (int i = 0; i < d.popsize; i++)
    {
        if (pop[i].fitness < best.fitness)
        {
            best = pop[i];
        }
    }
    return best;
}

void write_best(chrom x, struct info d)
{
    printf("\nBest individual: %4.1f\n", x.fitness);
    for (int i = 0; i < d.numGenes; i++)
        printf("%d", x.p[i]);
    putchar('\n');
}

// Avaliacao da população
// Parâmetros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Parâmetros de saída: Preenche pop com os valores de fitness e de validade para cada solução
void evaluate(pchrom pop, struct info d, int **mat)
{
    for (int i = 0; i < d.popsize; i++)
    {
        pop[i].fitness = (float)calcula_fit(pop[i].p, mat, d.numGenes);
    }
}

// Preenche uma estrutura com os progenitores da próxima geração, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Parâmetros de entrada: população actual (pop), estrutura com parâmetros (d) e população de pais a encher
void tournament(pchrom pop, struct info d, pchrom parents)
{
    int x1, x2;
    for (int i = 0; i < d.popsize; i++)
    {
        x1 = random_l_h(0, d.popsize - 1);
        do
        {
            x2 = random_l_h(0, d.popsize - 1);
        } while (x1 == x2);
        if (pop[x1].fitness < pop[x2].fitness)
            parents[i] = pop[x1];
        else
            parents[i] = pop[x2];
    }
}

// Operadores geneticos a usar na geração dos filhos
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void genetic_operators(pchrom parents, struct info d, pchrom offspring)
{
    crossover(parents, d, offspring); // Recombinação com um ponto de corte

    // mutation(offspring, d); // Mutação binária
}

// Preenche o vector descendentes com o resultado das operações de recombinação
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void crossover(pchrom parents, struct info d, pchrom offspring)
{
    for (int i = 0; i < d.popsize; i += 2)
    {
        if (rand_01() < d.pr)
        {
            int point = random_l_h(0, d.numGenes - 1);
            for (int j = 0; j < point; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i + 1].p[j];
            }
            for (int j = point; j < d.numGenes; j++)
            {
                offspring[i].p[j] = parents[i + 1].p[j];
                offspring[i + 1].p[j] = parents[i].p[j];
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i + 1] = parents[i + 1];
        }
        offspring[i].fitness = adjustOffspring(offspring[i].p, offspring[i].fitness, d);
        offspring[i + 1].fitness = adjustOffspring(offspring[i + 1].p, offspring[i + 1].fitness, d);
    }
}

// Mutação binária com vários pontos de mutação
// Parâmetros de entrada: estrutura com os descendentes (offspring) e estrutura com parâmetros (d)
void mutation(pchrom offspring, struct info d)
{
    for (int i = 0; i < d.popsize; i++)
    {
        for (int j = 0; j < d.numGenes; j++)
        {
            if (rand_01() < d.pm)
            {
                offspring[i].p[j] = !(offspring[i].p[j]);
            }
        }
    }
}

// Penaliza o custo dos filhos se a solucao for invalida
// Parâmetros de entrada: conjusto descendente a ser avaliado(offspring) e estrutura com parâmetros (d)
float adjustOffspring(int *offspring, float fitness, struct info d)
{
    int verts = 0, pen;
    for (int i = 0; i < d.numGenes; i++)
    {
        if (offspring[i] == 1)
            verts++;
    }
    if (d.capacity > verts)
        pen = (d.capacity - verts) * 100;
    else
        pen = (verts - d.capacity) * 100;

    return fitness - pen;
}