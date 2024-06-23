#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define POPULATION_SIZE 50     // Tamanho da população
#define NUM_GENES 2            // Número de genes por indivíduo
#define MAX_GENERATIONS 1000   // Número máximo de gerações
#define MUTATION_RATE 0.01     // Taxa de mutação

// Função Rastrigin para otimização
double rastrigin(double genes[NUM_GENES]) {
    double result = 10 * NUM_GENES; // Valor constante para a função Rastrigin
    for (int i = 0; i < NUM_GENES; i++) {
        result += genes[i] * genes[i] - 10 * cos(2 * M_PI * genes[i]); // Fórmula da função Rastrigin
    }
    return result;
}

// Inicializa a população com valores aleatórios dentro do intervalo [-5.0, 5.0]
void initialize_population(double population[POPULATION_SIZE][NUM_GENES]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < NUM_GENES; j++) {
            population[i][j] = (rand() / (double)RAND_MAX) * 10.0 - 5.0; // Gera valores aleatórios
        }
    }
}

// Avalia o fitness (aptidão) de toda a população usando a função Rastrigin
void evaluate_population(double population[POPULATION_SIZE][NUM_GENES], double fitness[POPULATION_SIZE]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        fitness[i] = rastrigin(population[i]); // Calcula o valor de fitness para cada indivíduo
    }
}

// Seleciona os pais para reprodução baseado no fitness (roleta simples)
void select_parents(double population[POPULATION_SIZE][NUM_GENES], double parents[POPULATION_SIZE][NUM_GENES], double fitness[POPULATION_SIZE]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        int parent1 = rand() % POPULATION_SIZE; // Seleciona aleatoriamente o primeiro pai
        int parent2 = rand() % POPULATION_SIZE; // Seleciona aleatoriamente o segundo pai
        // Escolhe o pai com melhor fitness para cada gene
        parents[i][0] = (fitness[parent1] < fitness[parent2]) ? population[parent1][0] : population[parent2][0];
        parents[i][1] = (fitness[parent1] < fitness[parent2]) ? population[parent1][1] : population[parent2][1];
    }
}

// Realiza o crossover de ponto único entre os pais para gerar os filhos
void crossover(double parents[POPULATION_SIZE][NUM_GENES], double offspring[POPULATION_SIZE][NUM_GENES]) {
    for (int i = 0; i < POPULATION_SIZE; i += 2) {
        double alpha = (rand() / (double)RAND_MAX); // Fator de mistura aleatório
        // Crossover de ponto único para cada par de pais
        offspring[i][0] = alpha * parents[i][0] + (1 - alpha) * parents[i + 1][0];
        offspring[i][1] = alpha * parents[i][1] + (1 - alpha) * parents[i + 1][1];
        offspring[i + 1][0] = alpha * parents[i + 1][0] + (1 - alpha) * parents[i][0];
        offspring[i + 1][1] = alpha * parents[i + 1][1] + (1 - alpha) * parents[i][1];
    }
}

// Aplica mutação aleatória aos filhos com base na taxa de mutação
void mutate(double offspring[POPULATION_SIZE][NUM_GENES]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < NUM_GENES; j++) {
            if ((rand() / (double)RAND_MAX) < MUTATION_RATE) { // Determina se ocorrerá mutação
                offspring[i][j] += (rand() / (double)RAND_MAX) * 2.0 - 1.0; // Gera valor de mutação
            }
        }
    }
}

// Algoritmo genético principal
void genetic_algorithm() {
    double population[POPULATION_SIZE][NUM_GENES];     // População de indivíduos
    double fitness[POPULATION_SIZE];                   // Array para armazenar o fitness de cada indivíduo
    double parents[POPULATION_SIZE][NUM_GENES];        // Array para os pais selecionados
    double offspring[POPULATION_SIZE][NUM_GENES];      // Array para os filhos gerados
    int generation = 0;                                // Contador de gerações

    initialize_population(population); // Inicializa a população aleatoriamente

    // Loop principal do algoritmo genético
    while (generation < MAX_GENERATIONS) {
        evaluate_population(population, fitness); // Avalia o fitness de toda a população
        select_parents(population, parents, fitness); // Seleciona os pais para reprodução
        crossover(parents, offspring); // Realiza o crossover para gerar os filhos
        mutate(offspring); // Aplica mutação nos filhos

        // Copia os filhos gerados de volta para a população
        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i][0] = offspring[i][0];
            population[i][1] = offspring[i][1];
        }

        generation++; // Incrementa o contador de gerações
    }

    // Avalia novamente o fitness da população final
    evaluate_population(population, fitness);
    double best_fitness = fitness[0]; // Melhor fitness encontrado
    int best_index = 0; // Índice do melhor indivíduo na população
    // Encontra o melhor indivíduo na população final
    for (int i = 1; i < POPULATION_SIZE; i++) {
        if (fitness[i] < best_fitness) {
            best_fitness = fitness[i];
            best_index = i;
        }
    }

    // Imprime a melhor solução encontrada
    printf("Best solution found: (%f, %f) with fitness %f\n", population[best_index][0], population[best_index][1], best_fitness);
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios
    genetic_algorithm(); // Chama o algoritmo genético principal
    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}




#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPULACAO 5

// Função para calcular a aptidão total
double calcular_aptidao_total(int aptidoes[], int tamanho) {
    double soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += aptidoes[i];
    }
    return soma;
}

// Função para calcular a roleta cumulativa
void calcular_roleta_cumulativa(double probabilidades[], double roleta_cumulativa[], int tamanho) {
    double acumulado = 0;
    for (int i = 0; i < tamanho; i++) {
        acumulado += probabilidades[i];
        roleta_cumulativa[i] = acumulado;
    }
}

// Função para selecionar um indivíduo baseado na roleta
void roleta_selecao(char populacao[], int aptidoes[], char selecao[], int tamanho) {
    double aptidao_total = calcular_aptidao_total(aptidoes, tamanho);
    
    double probabilidades[tamanho];
    for (int i = 0; i < tamanho; i++) {
        probabilidades[i] = aptidoes[i] / aptidao_total;
    }
    
    double roleta_cumulativa[tamanho];
    calcular_roleta_cumulativa(probabilidades, roleta_cumulativa, tamanho);
    
    for (int i = 0; i < tamanho; i++) {
        double r = (double)rand() / RAND_MAX;
        for (int j = 0; j < tamanho; j++) {
            if (r <= roleta_cumulativa[j]) {
                selecao[i] = populacao[j];
                break;
            }
        }
    }
}

int main() {
    // Inicializando o gerador de números aleatórios
    srand(time(NULL));
    
    char populacao[POPULACAO] = {'A', 'B', 'C', 'D', 'E'};
    int aptidoes[POPULACAO] = {10, 20, 30, 25, 15};
    char selecao[POPULACAO];
    
    roleta_selecao(populacao, aptidoes, selecao, POPULACAO);
    
    printf("Pais selecionados: ");
    for (int i = 0; i < POPULACAO; i++) {
        printf("%c ", selecao[i]);
    }
    printf("\n");
    
    return 0;
}