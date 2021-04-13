#A Simple Ilustrative Makefile for soshell

#

CC=cc

FLAGS=-c -Wall

OBS=main.o parse.o ficheiro2Memoria.o FCFS.o SJFS.o PRIORIDADE.o ListaMemoria.o gerir_Fits.o gestor_de_processos.o gerir_processo_Preemptivo.o execute.o LongoPrazo.o report.o

all :  projeto


main.o : biblioteca.h main.c

	$(CC) $(FLAGS) main.c

SJFS.o : biblioteca.h SJFS.c

	$(CC) $(FLAGS) SJFS.c

execute.o : biblioteca.h execute.c

	$(CC) $(FLAGS) execute.c
PRIORIDADE.o : biblioteca.h PRIORIDADE.c
	
	$(CC) $(FLAGS) PRIORIDADE.c

parse.o : biblioteca.h parse.c

	$(CC) $(FLAGS) parse.c

ficheiro2Memoria.o : biblioteca.h ficheiro2Memoria.c

	$(CC) $(FLAGS) ficheiro2Memoria.c

gerir_processo_Preemptivo.o : biblioteca.h gerir_processo_Preemptivo.c

	$(CC) $(FLAGS) gerir_processo_Preemptivo.c

FCFS.o: biblioteca.h FCFS.c

	$(CC) $(FLAGS) FCFS.c

gestor_de_processos.o : biblioteca.h gestor_de_processos.c

	$(CC) $(FLAGS) gestor_de_processos.c

LongoPrazo.o: biblioteca.h LongoPrazo.c

	$(CC) $(FLAGS) LongoPrazo.c

report.o: biblioteca.h report.c

	$(CC) $(FLAGS) report.c

ListaMemoria.o: biblioteca.h ListaMemoria.c

	$(CC) $(FLAGS) ListaMemoria.c

gerir_Fits.o: biblioteca.h gerir_Fits.c

	$(CC) $(FLAGS) gerir_Fits.c

projeto : $(OBS)

	$(CC)  -o projeto  $(OBS)


clean limpar:

	rm -f projeto *.o *~
	Limpeza total dos ficheiros