#include "exame.h"
#include "fila.h"
#include "laudo.h"
#include "patologia.h"
#include "simulacao.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMERO_PATOLOGIAS 5

void calcularEMostrarMetricas(Fila *filaLaudo, int tempo) {
  int totalLaudos = filaLaudo->tamanho;
  int laudosConcluidos = 0;
  int tempoEsperaTotal = 0;

  Fila *filaTemporaria = inicializarFila();

  while (!filaVazia(filaLaudo)) {
    int idPaciente = filaLaudo->inicio->dado;
    int condicao = filaLaudo->inicio->condicao;
    int instanteTempo = filaLaudo->inicio->instante_tempo;
    int tempoEspera = filaLaudo->inicio->tempo_espera;

    if (existeMedicoDisponivel()) {
      laudosConcluidos++;
      tempoEsperaTotal += tempoEspera;


      if (condicao >= 1 && condicao <= NUMERO_PATOLOGIAS) {
        estatisticas_patologias[condicao - 1].total_exames++;
        estatisticas_patologias[condicao - 1].tempo_total_espera += tempoEspera;
      }
    }

    desenfileirar(filaLaudo);


    enfileirarLaudo(filaTemporaria, idPaciente, condicao, instanteTempo,
                    tempoEspera);
  }

  
  while (!filaVazia(filaTemporaria)) {
    enfileirarLaudo(filaLaudo, filaTemporaria->inicio->dado,
                    filaTemporaria->inicio->condicao,
                    filaTemporaria->inicio->instante_tempo,
                    filaTemporaria->inicio->tempo_espera);

    desenfileirar(filaTemporaria);
  }

  liberarFila(filaTemporaria);

  imprimir(CONSOLE, "Total de laudos concluídos até o momento: %d\n", laudosConcluidos);
  imprimir(ARQUIVO, "Total de laudos concluídos até o momento: %d\n", laudosConcluidos);
  if (laudosConcluidos > 0) {
    imprimir(CONSOLE, "Tempo médio de espera para laudo: %.2f unidades de tempo\n",
       (float)tempoEsperaTotal / laudosConcluidos);
    imprimir(ARQUIVO, "Tempo médio de espera para laudo: %.2f unidades de tempo\n",
       (float)tempoEsperaTotal / laudosConcluidos);
    
  } else {
     imprimir(CONSOLE, "Ainda não há laudos concluídos.\n");
     imprimir(ARQUIVO, "Ainda não há laudos concluídos.\n");
  }
  imprimir(CONSOLE, "Percentual de laudos concluídos: %.2f%%\n",
     (float)laudosConcluidos / totalLaudos * 100);
  imprimir(ARQUIVO, "Percentual de laudos concluídos: %.2f%%\n",
     (float)laudosConcluidos / totalLaudos * 100);
  char saude[50];


  for (int i = 0; i < NUMERO_PATOLOGIAS; ++i) {
          if (i == 0) {
              strcpy(saude, "Saude Normal (gravidade 1)");
          } else if (i == 1) {
              strcpy(saude, "Bronquite (gravidade 2)");
          } else if (i == 2) {
              strcpy(saude, "Pneumonia (gravidade 3)");
          } else if (i == 3) {
              strcpy(saude, "Fratura de Fêmur (gravidade 4)");
          } else if (i == 4) {
              strcpy(saude, "Apendicite (gravidade 4)");
          }

          imprimir(CONSOLE, "Média de espera para Condição %s: %.2f unidades de tempo\n", saude,
                   estatisticas_patologias[i].total_exames > 0
                       ? (float)estatisticas_patologias[i].tempo_total_espera /
                             estatisticas_patologias[i].total_exames
                       : 0.0);
          imprimir(ARQUIVO, "Média de espera para Condição %s: %.2f unidades de tempo\n", saude,
                   estatisticas_patologias[i].total_exames > 0
                       ? (float)estatisticas_patologias[i].tempo_total_espera /
                             estatisticas_patologias[i].total_exames
                       : 0.0);
      }
  }