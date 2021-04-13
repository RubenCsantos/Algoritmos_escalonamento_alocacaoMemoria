#include "biblioteca.h"

void LongoPrazo()
{
	int tamanho = sizeFila(Bloqueados);
	int pos;
	int i=0;
	Nodo *aux= Bloqueados,*elemento = NULL;

	pos = rand() % (tamanho-1);

	if(Bloqueados == NULL)
	{
		//printf("Estou vazio!\n");
		return;
	}

	if(tamanho == 1)
	{
		elemento = obterElementoExecucao(&Bloqueados);
		elemento->pcb->estado = 0;
		pushFila3(&readyQueue,elemento);

		return;
	}

	while(i != pos-1)
	{
		aux=aux->nseg;
		i++;
	}

	elemento = obterElemento(&Bloqueados,aux);
	elemento->pcb->estado = 0;
	pushFila3(&readyQueue,elemento);
	aux_numero_de_processos--;
	return;
}

