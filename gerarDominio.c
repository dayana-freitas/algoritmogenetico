#include <stdio.h>

int intervalo_inicial = -5; 
int intervalo_final = 5;
int quant_itens_dominio = 0;
double taxa_mutacao_dominio = 0.5;

void gerarDominio() {
    quant_itens_dominio = (intervalo_final - intervalo_inicial) / taxa_mutacao_dominio + 1;
    printf("\n Quantidade de itens no domínio: %d", quant_itens_dominio);
    double vetor_dominio[quant_itens_dominio]; 
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
}

int main()
{
    gerarDominio();
    return 0;
}
