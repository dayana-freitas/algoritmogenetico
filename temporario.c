#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define tamanho_populacao 800 
//int tamanho_populacao = 10; // Tamanho da população que será gerada (Sempre números pares)
int intervalo_inicial = -1; // Intervalo do domínio de f(x)
int intervalo_final = 1;
double taxa_mutacao_dominio = 1; // Taxa na qual vai ser gerado o domínio de f(x) indo de intervalo_inicial até intervalo_final

double* gerarDominio(int quant_itens_dominio, double* vetor_dominio);
double calcularCusto(double coeficiente_a, double coeficiente_b, double coeficiente_c, double coeficiente_d, int quant_itens_dominio, double* vetor_dominio);
double** inicializarPopulacao(int quant_itens_dominio, double* dominio);
int* selecionarPais(int* indice, double* custo, int* selecao);
double** crossover(double* pai1, double* pai2, double* filho1, double* filho2);

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com uma semente baseada no tempo atual
    setlocale(LC_ALL, NULL); // Configurações de localidade

    int condicao = 0; // Enquanto condição for zero, o loop executará. Quando for um o valor ideal para os parametros da função foram encontrado ou a execução chegou ao limite
    int geracao = 0;
    printf("\n\n Algoritmo genético para ajuste de coeficientes da função f(x) = -a + bx - cx² + dx³ \n");
    const int quant_itens_dominio = round((intervalo_final - intervalo_inicial) / taxa_mutacao_dominio + 1);
    int indice[tamanho_populacao];
    int selecao[tamanho_populacao];
    double custo[tamanho_populacao];
    double vetor_dominio[quant_itens_dominio];
    double* dominio = gerarDominio(quant_itens_dominio, vetor_dominio); // Vetor dominio[] recebe o retorno da função gerarDominio
    double** populacao = inicializarPopulacao(quant_itens_dominio, dominio); // vetor populacao[][4] recebe o retorno da funcao inicializarPopulacao

    do {
        // Cálculo dos custos
        printf("\n\n Calculando o custo de cada cromossomo ...");
        for (int i = 0; i < tamanho_populacao; i++) {
            custo[i] = calcularCusto(populacao[i][0], populacao[i][1], populacao[i][2], populacao[i][3], quant_itens_dominio, dominio);
            indice[i] = i;
            printf("\n Custo do cromossomo %d: %lf", i, custo[i]);
        }
        double menor = 0;
        for (int i = 0; i < tamanho_populacao; i++) {
            
            if (custo[i] <= 0.0099) {
                if (menor > custo[i])
                {
                    menor = custo[i];
                }
                
                printf("\n\n Os coeficientes ideais encontrados foram em %d com custo de %.6f na geraçao %d\n ", i, custo[i], geracao);
                printf(" Coeficiente a = %.6f\n", populacao[i][0]);
                printf(" Coeficiente b = %.6f\n", populacao[i][1]);
                printf(" Coeficiente c = %.6f\n", populacao[i][2]);
                printf(" Coeficiente d = %.6f\n", populacao[i][3]);
                condicao = 1;
                break;
            }
        }
        if (condicao == 1) break;

        printf("\n\n Esta geração não possui coeficientes ideais para ajustar a função. Uma nova geração será criada!!! \n");

        // Seleção dos pais
        printf("\n Selecionando pais para a nova geração ... \n");
        int* pais = selecionarPais(indice, custo, selecao);

        printf("\n Pais selecionados: ");
        for (int i = 0; i < tamanho_populacao; i++) {
            printf("%d ", pais[i]);
        }

        // Crossover
        printf("\n\n Realizando crossover ...");
        int pai_temp = 0;
        double pai1[4], pai2[4], filho1[4], filho2[4];
        for (int i = 0; i < tamanho_populacao; i = i + 2) {
            for (int j = 0; j < 4; j++) {
                pai_temp = pais[i];
                pai1[j] = populacao[pai_temp][j];
            }
            printf("\n ");
            for (int j = 0; j < 4; j++) {
                int pai_temp = pais[i + 1];
                pai2[j] = populacao[pai_temp][j];
            }
            double** filhos = crossover(pai1, pai2, filho1, filho2);
            for (int j = 0; j < 4; j++)
            {
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
        printf("\n\n NOVA GERAÇÃO %d\n", geracao);
        for (int i = 0; i < tamanho_populacao; i++) {
            printf("\n ");
            for (int j = 0; j < 4; j++) {
                printf(" [ %.6f ] ", populacao[i][j]);
            }
        }
        condicao = 0;
        geracao++;
    } while (condicao == 0 && geracao <= 100);
    // Libera memória alocada para a população
    for (int i = 0; i < tamanho_populacao; i++) {
        free(populacao[i]);
    }
    free(populacao);
    return 0;
}

double* gerarDominio(int quant_itens_dominio, double* vetor_dominio) {
    int posicao_dominio = 0;
    double item_dominio = intervalo_inicial;
    printf("\n\n Vetor domínio: [");
    while (posicao_dominio < quant_itens_dominio)
    {
        vetor_dominio[posicao_dominio] = item_dominio;
        printf(" %.2f", vetor_dominio[posicao_dominio]);
        item_dominio = item_dominio + taxa_mutacao_dominio;
        posicao_dominio++;
    }
    printf(" ]");
    printf("\n Quantidade de itens no domínio: %d \n", quant_itens_dominio);
    return vetor_dominio;
}

double calcularCusto(double coeficiente_a, double coeficiente_b, double coeficiente_c, double coeficiente_d, int quant_itens_dominio, double* vetor_dominio) {
    double somatoria = 0;
    double RMSE = 0;
    double fx_ideal = 0;
    double fx = 0;
    int item = 0;
    printf("\n");

    while (item < quant_itens_dominio)
    {
        fx_ideal = -0.3 + 0.1 * vetor_dominio[item] - 0.5 * pow(vetor_dominio[item], 2) + 0.4 * pow(vetor_dominio[item], 3);
        fx = -coeficiente_a + coeficiente_b * vetor_dominio[item] - coeficiente_c * pow(vetor_dominio[item], 2) + coeficiente_d * pow(vetor_dominio[item], 3);
        somatoria = somatoria + pow((fx_ideal - fx), 2);
        // printf("\n f(x*) = %.2f ", fx_ideal);
        // printf("\n f(x) = %.2f", fx);
        item++;
    }

    RMSE = sqrt((somatoria / quant_itens_dominio));
    return RMSE;
    // Calcula o custo para cada cromossomo com base em seus coeficientes
}

double** inicializarPopulacao(int quant_itens_dominio, double* dominio) {
    double** populacao = (double**)malloc(tamanho_populacao * sizeof(double*));
    for (int i = 0; i < tamanho_populacao; i++) {
        populacao[i] = (double*)malloc(4 * sizeof(double));
    }

    double coeficiente_a = 0, coeficiente_b = 0, coeficiente_c = 0, coeficiente_d = 0;
    int cromossomo = 0;

    // Inicializa população com valores fornecidos pelo usuário
    // while (cromossomo < tamanho_populacao) {
    //     printf(" Digite o valor do coeficiente a : ");
    //     scanf("%lf", &coeficiente_a);
    //     populacao[cromossomo][0] = coeficiente_a;
    //     printf(" Digite o valor do coeficiente b : ");
    //     scanf("%lf", &coeficiente_b);
    //     populacao[cromossomo][1] = coeficiente_b;
    //     printf(" Digite o valor do coeficiente c : ");
    //     scanf("%lf", &coeficiente_c);
    //     populacao[cromossomo][2] = coeficiente_c;
    //     printf(" Digite o valor do coeficiente d : ");
    //     scanf("%lf", &coeficiente_d);
    //     populacao[cromossomo][3] = coeficiente_d;
    //     cromossomo++;
    //     printf("\n\n");
    // }
    double i = 1;
    while (cromossomo < tamanho_populacao) {
        coeficiente_a = i/tamanho_populacao;
        coeficiente_b = i/tamanho_populacao;
        coeficiente_c = i/tamanho_populacao;
        coeficiente_d = i/tamanho_populacao;
        populacao[cromossomo][0] = coeficiente_a;
        populacao[cromossomo][1] = coeficiente_b;
        populacao[cromossomo][2] = coeficiente_c;
        populacao[cromossomo][3] = coeficiente_d;
        cromossomo++;
        i++;
    }
    // while (cromossomo < tamanho_populacao) {
    //     coeficiente_a = srand();
    //     coeficiente_b = srand();
    //     coeficiente_c = srand();
    //     coeficiente_d = srand();
    //     populacao[cromossomo][0] = coeficiente_a;
    //     populacao[cromossomo][1] = coeficiente_b;
    //     populacao[cromossomo][2] = coeficiente_c;
    //     populacao[cromossomo][3] = coeficiente_d;
    //     cromossomo++;
    // }

    // Exibição da população inicial
    printf(" Tamanho da população: %d\n", tamanho_populacao);
    printf("\n GERAÇÃO INICIAL\n");
    for (int i = 0; i < tamanho_populacao; i++) {
        printf("\n");
        for (int j = 0; j < 4; j++) {
            printf(" [ %.6f ] ", populacao[i][j]);
        }
    }

    return populacao;
}

int* selecionarPais(int* indice, double* custo, int* selecao)
{
    double soma_inverso_custo = 0.0;
    for (int i = 0; i < tamanho_populacao; i++) {
        soma_inverso_custo += 1.0 / custo[i];
        // printf("\n Soma Custo %.6f", soma_inverso_custo);
    }

    double probabilidades[tamanho_populacao];
    for (int i = 0; i < tamanho_populacao; i++) {
        probabilidades[i] = (1.0 / custo[i]) / soma_inverso_custo;
        // probabilidades[i] = -(custo[i] / soma_custo);
        // printf("\n Probabilidades: %f", probabilidades[i]);
    }

    double roleta_cumulativa[tamanho_populacao];
    double acumulado = 0.0;
    for (int i = 0; i < tamanho_populacao; i++) {
        acumulado += probabilidades[i];
        roleta_cumulativa[i] = acumulado;
        // printf("\n Roleta Cumulativa: %f", roleta_cumulativa[i]);
    }

    for (int i = 0; i < tamanho_populacao; i++) {
        double r = (double)rand() / RAND_MAX;
        // printf("\n RRRRRRRR %f", r);
        for (int j = 0; j < tamanho_populacao; j++) {
            if (r <= roleta_cumulativa[j]) {
                selecao[i] = indice[j];
                // printf("\n Seleção: %d", selecao[i]);
                break;
            }
        }
    }
    return selecao;
}

double** crossover(double* pai1, double* pai2, double* filho1, double* filho2)
{
    // Alocação de memória para a variável filhos
    double** filhos = (double**)malloc(tamanho_populacao * sizeof(double*));
    for (int i = 0; i < 2; i++) {
        filhos[i] = (double*)malloc(4 * sizeof(double));
    }

    int ponto_corte = rand() % 4;

    for (int i = 0; i < 4; i++) {
        if (i < ponto_corte) {
            filho1[i] = pai1[i];
            filho2[i] = pai2[i];
        }
        else {
            filho1[i] = pai2[i];
            filho2[i] = pai1[i];
        }
    }

    for (int i = 0; i < 4; i++) {
        filhos[0][i] = filho1[i];
    }
    for (int i = 0; i < 4; i++) {
        filhos[1][i] = filho2[i];
    }

    // Apresenta os pais iniciais
    // printf("\n Pais: \n");
    // for (int j = 0; j < 4; j++) {
    //     printf(" [ %.6f ] ", pai1[j]);
    // }
    // printf("\n");
    // for (int j = 0; j < 4; j++) {
    //     printf(" [ %.6f ] ", pai2[j]);
    // }
    // printf("\n Ponto de corte: %d", ponto_corte);
    // // Apresenta os filhos gerados
    // printf("\n Filhos: \n");
    // for (int j = 0; j < 4; j++) {
    //     printf(" [ %.6f ] ", filhos[0][j]);
    // }
    // printf("\n");
    // for (int j = 0; j < 4; j++) {
    //     printf(" [ %.6f ] ", filhos[1][j]);
    // }
    return filhos;
}