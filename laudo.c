#include "laudo.h"
#include "exame.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>

int gerarCondicaoAleatoria() {
    
    double probabilidade = (double)rand() / (RAND_MAX + 1);

    if (probabilidade < 0.3) {
        return 1;  
    } else if (probabilidade < 0.5) {
        return 2;  
    } else if (probabilidade < 0.7) {
        return 3;  
    } else if (probabilidade < 0.85) {
        return 4;  
    } else {
        return 5;  
    }
}

void gerarLaudo(Fila *filaExames, Fila *filaLaudo,
                int *radiologistasDisponiveis, int tempo) {
    static int numeroPaciente = 1;

    if (!filaVazia(filaExames) && *radiologistasDisponiveis > 0) {
        int idPaciente = desenfileirar(filaExames);
        int tempoPreparoLaudo = rand() % 21 + 10;

        RegistroLaudo novoLaudo;
        novoLaudo.id_paciente = idPaciente;
        int condicao = gerarCondicaoAleatoria();
        novoLaudo.condicao = condicao;
        novoLaudo.instante_tempo = tempo + tempoPreparoLaudo;
        novoLaudo.tempo_espera = tempo - novoLaudo.instante_tempo;

        imprimir(CONSOLE, "Tempo %d: Laudo para Paciente %d concluído em %d unidades de tempo. Condição: %d.",
                 tempo + tempoPreparoLaudo, idPaciente, tempoPreparoLaudo,
                 novoLaudo.condicao);

        imprimir(ARQUIVO, "Tempo %d: Laudo para Paciente %d concluído em %d unidades de tempo. Condição: %d.",
                 tempo + tempoPreparoLaudo, idPaciente, tempoPreparoLaudo,
                 novoLaudo.condicao);

        No *atual = filaLaudo->inicio;
        while (atual != NULL) {
            atual->tempo_espera = tempo - atual->instante_tempo;
            atual = atual->proximo;
        }

        enfileirarLaudo(filaLaudo, numeroPaciente, novoLaudo.condicao,
                        novoLaudo.instante_tempo, novoLaudo.tempo_espera);
        (*radiologistasDisponiveis)++;
        numeroPaciente++;
    }
}