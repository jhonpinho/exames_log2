#ifndef LOGGING_H
#define LOGGING_H
#include <stdio.h>

typedef enum {
    CONSOLE,
    ARQUIVO
} Destino;

void imprimir(Destino destino, const char *format, ...);

#endif