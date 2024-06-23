#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double* selecionarPais(double* populacao, double *custo, double *selecao, int tamanho)
{
    printf("\n Velhos: %f  %f  %f  %f  %f", custo[0], custo[1], custo[2],  custo[3],  custo[4]);
    double soma_custo = 0;
    for (int i = 0; i < tamanho; i++) {
        soma_custo += custo[i];
        printf("\n Soma Custo: %f ", soma_custo);
    }
    
    double probabilidades[tamanho];
    for (int i = 0; i < tamanho; i++) {
        probabilidades[i] = custo[i] / soma_custo;
        printf("\n Probabilidades: %f  %f  %f  %f  %f", probabilidades[0], probabilidades[1], probabilidades[2],  probabilidades[3],  probabilidades[4]);
    }
    
    double roleta_cumulativa[tamanho];
    double acumulado = 0;
    for (int i = 0; i < tamanho; i++) {
        acumulado += probabilidades[i];
        roleta_cumulativa[i] = acumulado;
        printf("\n Roleta Cumulativa: %f  %f  %f  %f  %f", roleta_cumulativa[0], roleta_cumulativa[1], roleta_cumulativa[2],  roleta_cumulativa[3],  roleta_cumulativa[4]);
    }
    
    for (int i = 0; i < tamanho; i++) {
        double r = (double)rand() / RAND_MAX;
        for (int j = 0; j < tamanho; j++) {
            if (r <= roleta_cumulativa[j]) {
                selecao[i] = populacao[j];
                printf("\n Seleção: %f  %f  %f  %f  %f", selecao[0], selecao[1], selecao[2],  selecao[3],  selecao[4]);
                break;
            }
        }
    }
    // return custo;

}
 
int main()
{
    srand(time(NULL)); // Inicializando o gerador de números aleatórios
    double populacao[5] = {1, 2, 3, 4, 5};
    double custo[5] = {0.1, 0.2, 0.3, 0.4, 0.5};
    double selecao[5];
    double* pais = selecionarPais(populacao, custo, selecao, 5);
    printf("\n Novos: %f  %f  %f  %f  %f", pais[0], pais[1], pais[2],  pais[3],  pais[4]);
    
    printf("\n Pais selecionados: ");
    for (int i = 0; i < 5; i++) {
        printf("%f ", selecao[i]);
    }
    printf("\n");

    return 0;
}