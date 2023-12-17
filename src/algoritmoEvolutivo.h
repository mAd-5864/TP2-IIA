#include "utils.h"

#define MAX_OBJ 1000 // Numero maximo de objectos

// EStrutura para armazenar parametros
struct info
{
    int popsize;        // Tamanho da população
    float pm;           // Probabilidade de mutação
    float pr;           // Probabilidade de recombinação
    int tsize;          // Tamanho do torneio para seleção do pai da próxima geração
    float ro;           // Constante para avaliação com penalização
    int numGenes;       // Número de vertices
    int capacity;       // Capacidade do conjunto(valor de K)
    int numGenerations; // Número de gerações
};

typedef struct individual chrom, *pchrom; // Individuo (solução)

struct individual
{
    int p[MAX_OBJ]; // Solução (objetos que estão dentro da mochila)
    float fitness;  // Valor da qualidade da solução
    int valido;     // 1 se for uma solução válida e 0 se não for
};

pchrom init_pop(struct info d);
chrom get_best(pchrom pop, struct info d, chrom best);
void write_best(chrom x, struct info d);
void evaluate(pchrom pop, struct info d, int **mat);
void tournament(pchrom pop, struct info d, pchrom parents);
void genetic_operators(pchrom parents, struct info d, pchrom offspring);
void crossover(pchrom parents, struct info d, pchrom offspring);
void mutation(pchrom offspring, struct info d);
float adjustOffspring(int *offspring, float fitness, struct info d);
int algoritmoEvolutivo(GraphData grafo, struct info d);