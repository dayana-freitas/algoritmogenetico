#include <stdio.h>
#include <string.h>

int main() {
    FILE* arquivo;
    char nome[100];
    int idade;
    int total_nomes = 0;

    // Abrir o arquivo para leitura
    fopen(&arquivo, "nomes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ler e imprimir cada nome e idade do arquivo
    printf("Nomes e Idades:\n");
    while (fscanf(arquivo, "%s %d", nome, sizeof(nome), &idade) == 2) {
        printf("Nome: %s, Idade: %d\n", nome, idade);
        total_nomes++;
    }

    // Fechar o arquivo de leitura
    fclose(arquivo);

    // Abrir o arquivo para adicionar novos nomes e idades
    fopen(&arquivo, "nomes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para adicionar novos nomes e idades.\n");
        return 1;
    }

    // Solicitar ao usuario para inserir novos nomes e idades
    printf("\nInsira novos nomes e idades (digite 'FIM' para parar):\n");
    while (1) {
        printf("Nome: ");
        if (scanf("%99s", nome, sizeof(nome)) != 1) {
            printf("Erro ao ler entrada.\n");
            break;
        }
        if (strcmp(nome, "FIM") == 0) {
            break;
        }
        printf("Idade: ");
        if (scanf("%d", &idade) != 1) {
            printf("Erro ao ler entrada.\n");
            break;
        }
        fprintf(arquivo, "%s %d\n", nome, idade);
        total_nomes++;
    }

    // Fechar o arquivo de escrita
    fclose(arquivo);

    printf("\nTotal de nomes disponiveis: %d\n", total_nomes);

    return 0;
}