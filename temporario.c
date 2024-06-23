        // Calcular a soma total dos fitness na população
        // double sumFitness = 0.0;
        // for (int i = 0; i < POPULATION_SIZE; i++) {
        //     sumFitness += fitness[i];
        // }

        // // Normalizar o fitness
        // double normalizedFitness[POPULATION_SIZE];
        // for (int i = 0; i < POPULATION_SIZE; i++) {
        //     normalizedFitness[i] = fitness[i] / sumFitness;
        // }

        /* Seleção de pais pelo método da roleta */

        // Calcular a soma total dos custos na população
        double soma_custo = 0.0;
        for (int i = 0; i < tamanho_populacao; i++) {
            soma_custo += populacao[i][4];
            printf("\n Soma do custo: %.5f ", soma_custo);
        }

        // Normalizar o custo
        double custo_normalizado[tamanho_populacao];
        for (int i = 0; i < tamanho_populacao; i++) {
            custo_normalizado[i] = populacao[i][4] / soma_custo;
        printf("\n Custo normalizado: %.5f ", custo_normalizado[i]);
        }

        // Girando roleta
        double r = (rand() / (double)RAND_MAX);
        double probabilidade_cumulativa = 0.0;
        double pais[tamanho_populacao];
        int num_pais_selecionados = 0;
        for (int i = 0; i < tamanho_populacao; i++) {
            probabilidade_cumulativa += custo_normalizado[i];
            if (r <= probabilidade_cumulativa) {
                // Selecionar o i-ésimo indivíduo como pai
                pais[num_pais_selecionados] = populacao[i][4];
                num_pais_selecionados++;
                printf("\n Numero de pais selecionados: %.5f ", pais[num_pais_selecionados]);

                break;
            }
        }
        num_pais_selecionados = 0;












        double custo = calcularCusto(coeficiente_a, coeficiente_b, coeficiente_c, coeficiente_d, quant_itens_dominio, dominio);
        printf("\n Custo: %.5f \n", custo);
        populacao[cromossomo][4] = custo;