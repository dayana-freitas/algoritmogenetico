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

    return 0;
}