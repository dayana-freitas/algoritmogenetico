#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tamanho_populacao = 5;

int* selecionarPais(int* indice, double *custo, int *selecao, int tamanho_populacao)
{
    double soma_custo = 0;
    for (int i = 0; i < tamanho_populacao; i++) {
        soma_custo += custo[i];
        printf("\n Soma Custo: %f ", soma_custo);
    }
    printf("\n");
    
    double probabilidades[tamanho_populacao];
    for (int i = 0; i < tamanho_populacao; i++) {
        probabilidades[i] = custo[i] / soma_custo;
        printf("\n Probabilidades: %f", probabilidades[i]);
    }
    printf("\n");
    
    double roleta_cumulativa[tamanho_populacao];
    double acumulado = 0;
    for (int i = 0; i < tamanho_populacao; i++) {
        acumulado += probabilidades[i];
        roleta_cumulativa[i] = acumulado;
        printf("\n Roleta Cumulativa: %f", roleta_cumulativa[i]);
    }
    printf("\n");
    
    for (int i = 0; i < tamanho_populacao; i++) {
        double r = (double)rand() / RAND_MAX;
        for (int j = 0; j < tamanho_populacao; j++) {
            if (r <= roleta_cumulativa[j]) {
                selecao[i] = indice[j];
                printf("\n Seleção: %d", selecao[i]);
                break;
            }
        }
    }
    printf("\n");
    return selecao;
}

void crossover(int* pai1, int* pai2, int* filho1, int* filho2, int tamanho)
{
    int ponto_corte = rand() % tamanho;
    printf("\n Ponto de Corte: %d\n", ponto_corte);
    
    for (int i = 0; i < tamanho; i++) {
        if (i < ponto_corte) {
            filho1[i] = pai1[i];
            filho2[i] = pai2[i];
        } else {
            filho1[i] = pai2[i];
            filho2[i] = pai1[i];
        }
    }
}

int main()
{
    srand(time(NULL)); // Inicializando o gerador de números aleatórios
    int indice[5] = {1, 2, 3, 4, 5};
    double custo[5] = {0.1, 0.2, 0.3, 0.4, 0.5};
    int selecao[5];
    int* pais = selecionarPais(indice, custo, selecao, 5);
    
    printf("\n\n Pais selecionados: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", pais[i]);
    }
    printf("\n");
    
    // Exemplo de uso do crossover
    int pai1[5] = {4, 2, 7, 4, 5};
    int pai2[5] = {5, 4, 3, 2, 1};
    int filho1[5], filho2[5];
    
    crossover(pai1, pai2, filho1, filho2, 5);
    printf("\nPai 1: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", pai1[i]);
    }
    printf("\nPai 2: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", pai2[i]);
    }
    printf("\n");

    printf("\nFilho 1: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", filho1[i]);
    }
    printf("\nFilho 2: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", filho2[i]);
    }
    printf("\n");

    return 0;
}
