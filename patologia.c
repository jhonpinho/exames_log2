#include "patologia.h"
#define NUMERO_PATOLOGIA 5
Patologia estatisticas_patologias[NUMERO_PATOLOGIA];

Patologia inicializarPatologia(int condicao) {
  Patologia patologia;
  patologia.id_patologia = condicao;
  patologia.total_exames = 0;
  patologia.tempo_total_espera = 0;

  return patologia;
}
