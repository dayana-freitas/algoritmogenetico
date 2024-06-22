#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int intervalo_inicial = -5; 
int intervalo_final = 5;
double taxa_mutacao_dominio = 0.5;

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

int main()
{
    int quant_itens_dominio = (intervalo_final - intervalo_inicial) / taxa_mutacao_dominio + 1;
    double vetor_dominio[21] = {0, 1, 2 ,3 ,4 , 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    double custo = calcularCusto(1, 1, 1, 1, quant_itens_dominio, vetor_dominio);
    printf("\n\n Custo: %.5f", custo);
    return 0;
}
