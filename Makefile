CC = gcc-11
CFLAGS = -Wall -Wextra

OBJS = fila.o laudo.o exame.o paciente.o patologia.o simulacao.o logging.o main.o

all: simulacao

simulacao: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o simulacao

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c

laudo.o: laudo.c laudo.h fila.h
	$(CC) $(CFLAGS) -c laudo.c

exame.o: exame.c exame.h fila.h laudo.h simulacao.h
	$(CC) $(CFLAGS) -c exame.c

paciente.o: paciente.c paciente.h
	$(CC) $(CFLAGS) -c paciente.c

patologia.o: patologia.c patologia.h
	$(CC) $(CFLAGS) -c patologia.c

simulacao.o: simulacao.c simulacao.h fila.h exame.h laudo.h paciente.h patologia.h logging.h
	$(CC) $(CFLAGS) -c simulacao.c

logging.o: logging.c logging.h
	$(CC) $(CFLAGS) -c logging.c

main.o: main.c fila.h exame.h laudo.h paciente.h patologia.h simulacao.h logging.h
	$(CC) $(CFLAGS) -c main.c

run: simulacao
	./simulacao

clean:
	rm -f $(OBJS) simulacao

