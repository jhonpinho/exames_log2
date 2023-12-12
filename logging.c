#include "logging.h"
#include <stdarg.h>

typedef enum Destino;

void imprimir(Destino destino, const char *formato, ...) {

  FILE *arquivoLog = fopen("log.txt", "a");
  va_list args;

  va_start(args, formato);

  if (destino == CONSOLE) {

    vprintf(formato, args);

  } else if (destino == ARQUIVO) {

    vfprintf(arquivoLog, formato, args);

    fprintf(arquivoLog, "\n");
  }

  va_end(args);

  fclose(arquivoLog);
}
