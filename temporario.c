#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int tamanho_populacao = 4; // Tamanho da população (Sempre números pares)
int intervalo_inicial = -1; // Intervalo do domínio de f(x)
int intervalo_final = 1;
double taxa_mutacao_dominio = 1; // Taxa de mutação do domínio

double* gerarDominio(int quant_itens_dominio, double *vetor_dominio);
double calcularCusto(double coeficiente_a, double coeficiente_b, double coeficiente_c, double coeficiente_d, int quant_itens_dominio, double *vetor_dominio);
double** inicializarPopulacao(int quant_itens_dominio, double *dominio);
int* selecionarPais(int* indice, double *custo, int *selecao, int tamanho_populacao);
double** crossover(double* pai1, double* pai2, double* filho1, double* filho2, int tamanho_populacao);

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com uma semente baseada no tempo atual
    setlocale(LC_ALL, NULL); // Configurações de localidade

    int condicao = 0; // Controle de loop

    printf("\n\n Algoritmo genético para ajuste de coeficientes da função f(x) = -a + bx - cx² + dx³ \n\n");

    do {
        // Geração do domínio
        int quant_itens_dominio = (intervalo_final - intervalo_inicial) / taxa_mutacao_dominio + 1;
        int indice[tamanho_populacao];
        int selecao[tamanho_populacao];
        double custo[tamanho_populacao];
        double vetor_dominio[quant_itens_dominio];
        double* dominio = gerarDominio(quant_itens_dominio, vetor_dominio); // Vetor dominio[] recebe o retorno da função gerarDominio
        double** populacao = inicializarPopulacao(quant_itens_dominio, dominio); // vetor populacao[][4] recebe o retorno da funcao inicializarPopulacao

        printf("\n\n Quantidade de itens no domínio: %d \n", quant_itens_dominio);

        // Cálculo dos custos
        for (int i = 0; i < tamanho_populacao; i++){
            custo[i] = calcularCusto(populacao[i][0], populacao[i][1], populacao[i][2], populacao[i][3], quant_itens_dominio, dominio);
            indice[i] = i;
            printf("\n Custo em %d é: %f", i, custo[i]);
        }

        // Seleção dos pais
        int* pais = selecionarPais(indice, custo, selecao, tamanho_populacao);

        printf("\n\n Pais selecionados: ");
        for (int i = 0; i < tamanho_populacao; i++) {
            printf("%d ", pais[i]);
        }

        printf("\n");
        int pai_temp = 0;
        double pai1[4], pai2[4], filho1[4], filho2[4];

        // Crossover
        for (int i = 0; i < tamanho_populacao; i = i + 2) {
            for (int j = 0; j < 4; j++) {
                pai_temp = pais[i];
                pai1[j] = populacao[pai_temp][j];
            }
            for (int j = 0; j < 4; j++) {
                pai_temp = pais[i + 1];
                pai2[j] = populacao[pai_temp][j];
            }
            double** filhos = crossover(pai1, pai2, filho1, filho2, tamanho_populacao);
            for (int j = 0; j < 4; j++) {
                populacao[i][j] = filhos[0][j];
                populacao[i + 1][j] = filhos[1][j];
            }
            // Libera memória alocada para os filhos
            for (int k = 0; k < 2; k++) {
                free(filhos[k]);
            }
            free(filhos);
        }

        // Exibição da nova população
        printf("\n Nova População: ");
        for (int i = 0; i < tamanho_populacao; i++) {
            printf("\n %d", i);
            for (int j = 0; j < 4; j++) {
                printf(" [ %.5f ] ", populacao[i][j]);
            }
        }

        // Verifica condição de parada (atualmente comentado)
        for (int i = 0; i < tamanho_populacao; i++) {
            if (custo[i] <= 0.01) {
                printf("\n\n Os coeficientes ideais encontrados foram: \n");
                printf(" Coeficiente a = %.5f\n", populacao[i][0]);
                printf(" Coeficiente b = %.5f\n", populacao[i][1]);
                printf(" Coeficiente c = %.5f\n", populacao[i][2]);
                printf(" Coeficiente d = %.5f\n", populacao[i][3]);
                condicao = 1;
                break;
            }
        }
        printf("\n\n Esta geração não possui coeficientes ideais para ajustar a função. Uma nova geração será criada!!! \n");

        // Libera memória alocada para a população
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
    while (posicao_dominio < quant_itens_dominio) { 
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
    printf("\n\n");

    while (item < quant_itens_dominio) {
        fx_ideal = - 0.3 + 0.1 * vetor_dominio[item] - 0.5 * pow( vetor_dominio[item], 2) + 0.4 * pow(vetor_dominio[item], 3);
        fx = - coeficiente_a + coeficiente_b * vetor_dominio[item] - coeficiente_c * pow( vetor_dominio[item], 2) + coeficiente_d * pow(vetor_dominio[item], 3);
        somatoria = somatoria + pow((fx_ideal - fx), 2);
        printf("\n f(x*) = %.2f ", fx_ideal);
        printf("\n f(x) = %.2f \n", fx);
        item++;
    } 
    RMSE = sqrt((somatoria / quant_itens_dominio));   
    return RMSE;
}

double** inicializarPopulacao(int quant_itens_dominio, double *dominio) {
    double** populacao = (double**)malloc(tamanho_populacao * sizeof(double*));
    for (int i = 0; i < tamanho_populacao; i++) {
        populacao[i] = (double*)malloc(4 * sizeof(double));
    }

    double coeficiente_a = 0, coeficiente_b = 0, coeficiente_c = 0, coeficiente_d = 0;
    int cromossomo = 0;

    // Inicializa população com valores fornecidos pelo usuário
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
        cromossomo++;
        printf(" \n \n ");
    }

    // Exibição da população inicial
    for (int i = 0; i < tamanho_populacao; i++) {
        printf("\n");
        for (int j = 0; j < 4; j++) {
            printf(" [ %.5f ] ", populacao[i][j]);
        }
    }

    return populacao;
}

int* selecionarPais(int* indice, double *custo, int *selecao, int tamanho_populacao) {
    printf("\n\n");
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

double** crossover(double* pai1, double* pai2, double* filho1, double* filho2, int tamanho_populacao) {
    double** filhos = (double**)malloc(2 * sizeof(double*));
    for (int i = 0; i < 2; i++) {
        filhos[i] = (double*)malloc(4 * sizeof(double));
    }
    int ponto_corte = rand() % 4; // Ponto de corte para crossover
    printf("\n Ponto de Corte: %d\n", ponto_corte);
    printf("\n Pais: \n");
    for (int j = 0; j < 4; j++) {
        printf(" [ %.5f ] ", pai1[j]);
    }
    printf("\n");

    for (int j = 0; j < 4; j++) {
        printf(" [ %.5f ] ", pai2[j]);
    }

    for (int i = 0; i < 4; i++) {
        if (i < ponto_corte) {
            filho1[i] = pai1[i];
            filho2[i] = pai2[i];
        } else {
            filho1[i] = pai2[i];
            filho2[i] = pai1[i];
        }
    }

    for (int i = 0; i < 4; i++) {
        filhos[0][i] = filho1[i];
        filhos[1][i] = filho2[i];
    }

    printf("\n Filhos: \n");
    for (int j = 0; j < 4; j++) {
        printf(" [ %.5f ] ", filhos[0][j]);
    }
    printf("\n");
    for (int j = 0; j < 4; j++) {
        printf(" [ %.5f ] ", filhos[1][j]);
    }
    return filhos;
}
