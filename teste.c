#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    double somatoria = 0;
    double custo = 0;
    int quant_itens_dominio = 4;
    double coeficiente_a = 1, coeficiente_b = 1, coeficiente_c = 1, coeficiente_d = 1;
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
        printf("\n f(x) = %.2f ", fx);
        printf("\n Somatória Parcial: %.2f \n", somatoria);
        x++;
    } 
    printf("\n\n Somatória Total: %.2f", somatoria);

    custo = sqrt((somatoria/quant_itens_dominio));
    printf("\n\n Custo: %.2f", custo);
    return custo;
}