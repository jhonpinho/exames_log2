#include "fila.h"
#include "laudo.h"
#include "logging.h"
#include "simulacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main() {

  srand(time(NULL));

  Fila *filaPacientes = inicializarFila(100);
  Fila *filaExames = inicializarFila(100);
  Fila *filaLaudo = inicializarFila(100);

  int idPaciente = 1;
  int aparelhosDisponiveis = 5;
  int radiologistasDisponiveis = 3;

  for (int tempo = 1; tempo <= 43200; tempo++) {

    simularChegadaPacientes(filaPacientes, &idPaciente, tempo);

    // Simulação de exames de raio-x
    simularExameRaioX(filaPacientes, filaExames, filaLaudo,
                      &aparelhosDisponiveis, tempo, &idPaciente);

    // Simulação de laudos
    simularLaudos(filaExames, filaLaudo, &radiologistasDisponiveis, tempo);

    // Simulação do sistema de logging para chegada de pacientes
    if (!filaVazia(filaPacientes)) {
      int idNovoPaciente = filaPacientes->inicio->dado;

      char log_info[256];
      snprintf(log_info, sizeof(log_info), "Tempo %d: Paciente %d chegou.",
               tempo, idNovoPaciente);
      imprimir(CONSOLE, "%s", log_info);
      imprimir(ARQUIVO, "%s", log_info);
    }

    // Simulação do sistema de logging para realização de exames
    if (!filaVazia(filaExames)) {
      int idExame = filaExames->inicio->dado;

      char log_info[256];
      snprintf(log_info, sizeof(log_info),
               "Tempo %d: Exame do Paciente %d realizado.", tempo, idExame);
      imprimir(CONSOLE, "%s", log_info);
      imprimir(ARQUIVO, "%s", log_info);
    }

    // Imprimir métricas e outras mensagens a cada 10 unidades de tempo
    if (tempo % 10 == 0) {
      imprimir(CONSOLE, "\n--- Relatório de Métricas (Tempo %d) ---", tempo);
      imprimir(ARQUIVO, "\n--- Relatório de Métricas (Tempo %d) ---", tempo);

      calcularEMostrarMetricas(filaLaudo, tempo);


      char log_info[256];
      snprintf(log_info, sizeof(log_info), "Tempo %d: Impressão de métricas.",
               tempo);
      imprimir(CONSOLE, "%s", log_info);
      imprimir(ARQUIVO, "%s", log_info);
    }

    // Sleep para simular passagem do tempo
    sleep(1);
  }

  // Liberar memória
  liberarFila(filaPacientes);
  liberarFila(filaExames);
  liberarFila(filaLaudo);

  return 0;
}