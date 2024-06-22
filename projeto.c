#include <stdio.h>
#include <math.h>

// Variáveis Globais
int intervalo_inicial = -1; // Somente números inteiros
int intervalo_final = 1;
double taxa_mutacao_dominio = 1;

// Protótipo das funções
double* gerarDominio(int quant_itens_dominio, double *vetor_dominio);
double calcularCusto(double coeficiente_a, double coeficiente_b, double coeficiente_c, double coeficiente_d, int quant_itens_dominio, double *vetor_dominio);

int main() {
    int quant_itens_dominio = (intervalo_final - intervalo_inicial) / taxa_mutacao_dominio + 1;
    printf("\n Quantidade de itens no domínio: %d \n", quant_itens_dominio);
    double vetor_dominio[quant_itens_dominio];
    double*  dominio = gerarDominio(quant_itens_dominio, vetor_dominio);
    double custo = calcularCusto(1, 1, 1, 1, quant_itens_dominio, dominio);
    printf("\n\n Custo: %.5f", custo);
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
    printf(" ]");    
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
    printf("\n\n Somatória Total: %.2f", somatoria);

    RMSE = sqrt((somatoria/quant_itens_dominio));
   
    return RMSE;
}