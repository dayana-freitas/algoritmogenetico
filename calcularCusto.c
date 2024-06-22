#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int quant_itens_dominio = 4;
double custo = 0;

double calcularCusto(double coeficiente_a, double coeficiente_b, double coeficiente_c, double coeficiente_d) {
    double somatoria = 0;
    int quant_itens_dominio = 4;
    double fx_ideal = 0;
    double fx = 0;
    int x = 0;
    double vetor_dominio[4] = {0, 1, 2, 3};
    while (x < quant_itens_dominio)
    {
        fx_ideal = - 0.3 + 0.1 * vetor_dominio[x] - 0.5 * pow( vetor_dominio[x], 2) + 0.4 * pow(vetor_dominio[x], 3);
        fx = - coeficiente_a + coeficiente_b * vetor_dominio[x] - coeficiente_c * pow( vetor_dominio[x], 2) + coeficiente_d * pow(vetor_dominio[x], 3);
        somatoria = somatoria + pow((fx_ideal - fx), 2);
        printf("\n f(x*) = %.2f ", fx_ideal);
        printf("\n f(x) = %.2f \n", fx);
        x++;
    } 
    printf("\n\n Somatória Total: %.2f", somatoria);

    custo = sqrt((somatoria/quant_itens_dominio));
   
    return custo;
}

int main()
{
    custo = calcularCusto(1, 1, 1, 1);
    printf("\n\n Custo: %.5f", custo);
    return 0;
}
