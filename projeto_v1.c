#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

// Variáveis Globais
int intervalo_inicial = -1; // Somente números inteiros
int intervalo_final = 1;
double taxa_mutacao_dominio = 0.5;
int tamanho_populacao = 3;
int cromossomo = 0;

// Protótipo das funções
double* gerarDominio(int quant_itens_dominio, double *vetor_dominio);
double calcularCusto(double coeficiente_a, double coeficiente_b, double coeficiente_c, double coeficiente_d, int quant_itens_dominio, double *vetor_dominio);
double** inicializarPopulacao(int quant_itens_dominio, double *dominio);

int main() {
    int condicao = 0;
    setlocale(LC_ALL,NULL);
    printf("\n\n Algoritmo Genético para ajuste de coeficientes da função f(x) = -a + bx - cx² + dx³\n\n");

    do {
        int quant_itens_dominio = (intervalo_final - intervalo_inicial) / taxa_mutacao_dominio + 1;
        printf("\n\n Quantidade de itens no domínio: %d \n", quant_itens_dominio);
        double vetor_dominio[quant_itens_dominio];
        double*  dominio = gerarDominio(quant_itens_dominio, vetor_dominio);
        double** populacao = inicializarPopulacao(quant_itens_dominio, dominio);

        for (int i = 0; i < tamanho_populacao; i++) {
            if (populacao[i][4] <= 0.01) {
                printf("\n\n Os coeficientes ideais encontrados foram: \n");
                printf(" Coeficiente a = %.5f\n", populacao[i][0]);
                printf(" Coeficiente b = %.5f\n", populacao[i][1]);
                printf(" Coeficiente c = %.5f\n", populacao[i][2]);
                printf(" Coeficiente d = %.5f\n", populacao[i][3]);
                condicao = 1;
                break;
            }
        }
        printf("\n\n Está geração não possui coeficientes ideais para ajustar a função. Uma nova geração será criada!!! \n");

        // Liberar memória alocada
        for (int i = 0; i < tamanho_populacao; i++) {
            free(populacao[i]);
        }
        free(populacao);
    } while (condicao == 0);
    
    return 0;
}

double* gerarDominio(int quant_itens_dominio, double *vetor_dominio) {
    int posicao_dominio = 0;
    double item_dominio = intervalo_inicial;
    printf("\n\n Vetor domínio: \n [");
    while (posicao_dominio < quant_itens_dominio)
    { 
        vetor_dominio[posicao_dominio] = item_dominio;
        printf(" %.2f", vetor_dominio[posicao_dominio]);
        item_dominio = item_dominio + taxa_mutacao_dominio;
        posicao_dominio++;
    }
    printf(" ] \n");    
    return vetor_dominio;
}

double calcularCusto(double coeficiente_a, double coeficiente_b, double coeficiente_c, double coeficiente_d, int quant_itens_dominio, double *vetor_dominio) {
    
    double somatoria = 0;
    double RMSE = 0;
    double fx_ideal = 0;
    double fx = 0;
    int item = 0;

    while (item < quant_itens_dominio)
    {
        fx_ideal = - 0.3 + 0.1 * vetor_dominio[item] - 0.5 * pow( vetor_dominio[item], 2) + 0.4 * pow(vetor_dominio[item], 3);
        fx = - coeficiente_a + coeficiente_b * vetor_dominio[item] - coeficiente_c * pow( vetor_dominio[item], 2) + coeficiente_d * pow(vetor_dominio[item], 3);
        somatoria = somatoria + pow((fx_ideal - fx), 2);
        printf("\n f(x*) = %.2f ", fx_ideal);
        printf("\n f(x) = %.2f \n", fx);
        item++;
    } 

    RMSE = sqrt((somatoria/quant_itens_dominio));
   
    return RMSE;
}

double** inicializarPopulacao(int quant_itens_dominio, double *dominio) {
    double** populacao = (double**)malloc(tamanho_populacao * sizeof(double*));
    for (int i = 0; i < tamanho_populacao; i++) {
        populacao[i] = (double*)malloc(5 * sizeof(double));
    }

    double coeficiente_a = 0, coeficiente_b = 0, coeficiente_c = 0, coeficiente_d = 0;
    int cromossomo = 0;

    while (cromossomo < tamanho_populacao) {
        printf(" Digite o valor do coeficiente a : ");
        scanf("%lf", &coeficiente_a);
        populacao[cromossomo][0] = coeficiente_a;
        printf(" Digite o valor do coeficiente b : ");
        scanf("%lf", &coeficiente_b);
        populacao[cromossomo][1] = coeficiente_b;
        printf(" Digite o valor do coeficiente c : ");
        scanf("%lf", &coeficiente_c);
        populacao[cromossomo][2] = coeficiente_c;
        printf(" Digite o valor do coeficiente d : ");
        scanf("%lf", &coeficiente_d);
        populacao[cromossomo][3] = coeficiente_d;

        double custo = calcularCusto(coeficiente_a, coeficiente_b, coeficiente_c, coeficiente_d, quant_itens_dominio, dominio);
        printf("\n Custo: %.5f \n", custo);
        populacao[cromossomo][4] = custo;
        cromossomo++;
    }

    for (int i = 0; i < tamanho_populacao; i++) {
        printf("\n");
        for (int j = 0; j < 5; j++) {
            printf(" [ %.5f ] ", populacao[i][j]);
        }
    }

    return populacao;
}